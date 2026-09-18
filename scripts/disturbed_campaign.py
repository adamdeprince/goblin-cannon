#!/usr/bin/env python3
"""Run declared simulated channel recovery, diversity and security selections."""
import argparse
import json
import platform
import subprocess
import sys
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/"tests/simulated_channel"))
from catalog import matrix


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("stage",choices=("security","latency","polar","diversity","repeat"))
    parser.add_argument("--git-commit",required=True)
    parser.add_argument("--source-digest",required=True)
    args=parser.parse_args()
    root=ROOT/"results/disturbed-recovery"
    root.mkdir(parents=True,exist_ok=True)
    base=[sys.executable,str(ROOT/"tests/simulated_channel/run.py"),"--profile","disturbed",
          "--git-commit",args.git_commit,"--source-digest",args.source_digest]
    cases=matrix();selections=[]
    if args.stage=="security":
        names={"A4_10000_64qam_offset_5","A4_10000_64qam_drift_10min","D3_auction_flood",
               "B1_10000_64qam_-20dB_1_100","B1_10000_64qam_-20dB_10_100",
               "B1_24000_64qam_-20dB_1_100","B1_24000_64qam_20dB_10_100",
               "B1_24000_64qam_20dB_10_1000","C4_generated_messages"}
        for tier in ("quick","full"):
            selected=[c.name for c in cases if c.tier==tier and c.parameters.get("campaign","matrix")=="matrix"
                      and (c.name in names or c.group in ("A8","D6","D4","B4","E1","C2"))]
            selections.append((tier,root/"security",selected,["--jobs","4"]))
    elif args.stage=="latency":
        target=root/"naamah-latency";target.mkdir(parents=True,exist_ok=True)
        host=dict(report_header="simulated channel quiet-host provenance",hostname=platform.node(),
                  platform=platform.platform(),source_tree_sha256=args.source_digest,git_commit=args.git_commit,
                  compiler=subprocess.check_output(["c++","--version"],text=True),
                  openssl=subprocess.check_output(["openssl","version","-a"],text=True))
        (target/"HOST.json").write_text(json.dumps(host,indent=2)+"\n")
        for tier in ("quick","full"):
            selected=[c.name for c in cases if c.group=="B5" and c.tier==tier and
                      c.parameters.get("campaign","matrix") in ("matrix","disturbed_latency")]
            selections.append((tier,target,selected,["--jobs","1","--allow-non-avx512"]))
    elif args.stage=="repeat":
        names=[f"D4_disturbed_{band}_qpsk_bch_null" for band in (10000,24000)]
        names += ["D4_disturbed_24000_bpsk_bch_null"]
        selections.append(("quick",root/"repeat",names,["--jobs","2"]))
    else:
        campaigns=("disturbed_quick","disturbed_screen","disturbed_followup") if args.stage=="polar" else ("disturbed_diversity","disturbed_delay")
        for campaign in campaigns:
            selected=[c.name for c in cases if c.parameters.get("campaign")==campaign]
            selections.append(("quick" if campaign.endswith("quick") else "full",root/args.stage,selected,
                               ["--jobs","4","--seeds","7446529","7446530","7446531"]))
    failures=[]
    for tier,target,selected,extra in selections:
        if not selected:raise RuntimeError("empty selection")
        command=base+["--tier",tier,"--results",str(target)]+extra
        for name in selected:command += ["--case",name]
        result=subprocess.run(command,cwd=ROOT)
        if result.returncode:failures.append(dict(tier=tier,results=str(target),code=result.returncode))
    print(json.dumps(dict(report_header="simulated channel campaign completion",stage=args.stage,failures=failures)))
    return bool(failures)


if __name__=="__main__":raise SystemExit(main())
