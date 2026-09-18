#!/usr/bin/env python3
"""Publish current recorded simulated channel evidence; no historical performance panels."""
import argparse
import hashlib
from pathlib import Path
import re
from disturbed_html import build

ROOT=Path(__file__).resolve().parents[1]
WEB=ROOT/"html"
START="    <!-- BEGIN GENERATED SIMULATED CHANNEL RESULTS -->"
END="    <!-- END GENERATED SIMULATED CHANNEL RESULTS -->"


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check",action="store_true")
    args=parser.parse_args()
    sections,js=build(START,END)
    index=WEB/"index.html"
    before,tail=index.read_text().split(START,1)
    _,after=tail.split(END,1)
    document=before+sections+after
    document=re.sub(r'^  <script defer src="(?:psk|encoding|refinement)-explorer\.js[^\"]*"></script>\n','',document,flags=re.M)
    for name,content in (("simulated-channel.js",js.encode()),("rf-explorer.js",(WEB/"rf-explorer.js").read_bytes()),("evidence.css",(WEB/"evidence.css").read_bytes())):
        version=hashlib.sha256(content).hexdigest()[:16]
        document=re.sub(r'((?:src|href)=")'+re.escape(name)+r'(?:\?[^" ]*)?"',lambda m:m.group(1)+name+"?v="+version+'"',document)
    outputs={index:document,WEB/"simulated-channel.js":js}
    stale=[p for p,value in outputs.items() if not p.exists() or p.read_text()!=value]
    if args.check:
        if stale:parser.exit(1,"Stale simulated channel HTML: "+", ".join(str(p.relative_to(ROOT)) for p in stale)+"\n")
        print("Current simulated channel HTML matches the recorded results.")
    else:
        for path,value in outputs.items():path.write_text(value)
        print("Published current simulated channel results.")


if __name__=="__main__":main()
