#!/usr/bin/env python3
"""Keep channel definitions and the measured boundary identical across documents."""
import argparse
from pathlib import Path
import re

from channel_description import (ROOT, boundary_text, scope_text, definitions_markdown,
                                 preset_markdown, RECORDED_OFFSETS)

START = "<!-- BEGIN CHANNEL CONTRACT -->"
END = "<!-- END CHANNEL CONTRACT -->"
PRIMARY = ("README.md", "TESTING.md", "html/README.md", "tests/README.md",
           "tests/simulated_channel/QUESTIONS.md", "docs/channel-model.md")


def block(full=False):
    sections = [START, "For the recorded acceptance profile:", boundary_text(), scope_text()]
    if full:
        sections += [definitions_markdown(), preset_markdown(), RECORDED_OFFSETS,
            "The carrier-offset sweep and its individual records are published in "
            "[the measurement report](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/SUMMARY.md). "
            "Historical results retain their original receiver versions and measurements."]
    sections.append(END)
    return "\n\n".join(sections)


def update(text, full=False):
    replacement = block(full)
    if START in text:
        before, tail = text.split(START, 1)
        _, after = tail.split(END, 1)
        return before + replacement + after
    # Some report generators already write the shared boundary; wrap that exact
    # paragraph rather than inserting a second copy.
    from channel_description import compact_markdown
    compact = compact_markdown()
    if compact in text:
        return text.replace(compact, replacement, 1)
    first, rest = text.split("\n", 1)
    return first + "\n\n" + replacement + "\n" + rest


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check",action="store_true")
    args=parser.parse_args()
    paths={ROOT/name for name in PRIMARY}
    paths.update(p for p in (ROOT/"results").rglob("*.md")
                 if "carrier-offset" not in p.parts and
                 re.search(r"simulated.channel|Watterson|Doppler|carrier correction",p.read_text(),re.I))
    stale=[]
    for path in sorted(paths):
        before=path.read_text()
        after=update(before,str(path.relative_to(ROOT)) in PRIMARY)
        if before!=after:
            stale.append(str(path.relative_to(ROOT)))
            if not args.check:path.write_text(after)
    if args.check and stale:parser.exit(1,"Stale channel wording: "+", ".join(stale)+"\n")
    print(f"Channel wording {'checked in' if args.check else 'updated across'} {len(paths)} documents.")


if __name__=="__main__":main()
