#!/usr/bin/env python3
"""Assert compact authenticated diversity delivery on a null simulated channel."""
import argparse
import concurrent.futures
import copy
import json
from pathlib import Path
import sys
import time

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tests/simulated_channel'))
from catalog import Case, matrix
from run import execute, persist, load_known

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--git-commit',required=True);parser.add_argument('--source-digest',required=True)
    parser.add_argument('--tier',choices=('quick',),default='quick')
    args=parser.parse_args();args.probe=ROOT/'build/goblin_cannon_simulated_channel_probe'
    target=ROOT/'results/disturbed-recovery/diversity-null';target.mkdir(parents=True,exist_ok=True)
    cases=[]
    for c in matrix():
        if c.parameters.get('campaign')!='disturbed_diversity' or c.parameters['delay_spread_ms']!=7:continue
        for seed in (7446529,7446530,7446531):
            p=copy.deepcopy(c.parameters)
            # Keep the existing harness's positive spread default even though
            # the fading stage is disabled; its constructor validates it.
            p.update(channel_model='null',delay_spread_ms=0,doppler_spread_hz=1,snr_db=None,duration_s=3,seed=seed,campaign='disturbed_diversity_null')
            name=c.name.replace('E2_','D4_',1).replace('_high_lat_disturbed','_null')
            cases.append(Case(name,'D4','assert','quick',p,checks=('messages_observed','no_corrupt_messages','no_duplicates'),
                              notes=['Null simulated channel with the 7 ms equalizer span; compact GCM and all recovery controls enabled.']))
    known=load_known();started=time.monotonic();statuses={}
    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
        for r in pool.map(lambda c:execute(c,args,known),cases):
            persist(r,target);statuses[r['status']]=statuses.get(r['status'],0)+1
    execution=dict(report_header='simulated channel compact diversity regression',kind='assert',tier='quick',
        git_commit=args.git_commit,source_tree_sha256=args.source_digest,elapsed_seconds=time.monotonic()-started,
        budget_seconds=120,executed_cases=len(cases),statuses=statuses,complete_tier=False,
        parameter_records=[f"{c.name}/{c.parameters['seed']}.json" for c in cases])
    (target/'EXECUTION-quick.json').write_text(json.dumps(execution,indent=2)+'\n');print(json.dumps(execution))
    return bool(set(statuses)-{'pass'})

if __name__=='__main__':raise SystemExit(main())
