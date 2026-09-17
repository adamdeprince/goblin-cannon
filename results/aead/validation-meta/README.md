# Simulated channel validation evidence

- `CTEST_AVX10.log` and `CTEST_NAAMAH.log`: final Release build tests, 21/21
  passing on each host. The corresponding `*_BUILD.json` binds each log hash
  to the tested source and records compiler, OpenSSL and CPU information.
- `HARNESS.json`: 14 deterministic harness checks; those checks also run in CTest.
- `HARNESS_METADATA.json` and log: all 14 checks pass after correcting stale
  descriptive metadata. `../METADATA_CORRECTION.json` proves that only three
  catalog descriptions changed relative to the tested source snapshot; original
  measurement source IDs, metrics, assertions and thresholds are preserved.
- `PYTHON_GRPC.json`: 19 CLI/protobuf serialization checks. Actual wrong-key
  RF/FEC reception and gRPC authentication-counter queries are covered by CTest.
- `BROWSER_LOCAL.json` and screenshots: all 72 current result views, 216 source
  links, both latency/defect tables, mobile layout and the no-JavaScript fallback.
- `INITIAL_XPASS_EXECUTION.json`: retained transition diagnostic from before the
  obsolete expected-failure entries were removed. Its four `fail` cases were
  unexpected **passes** under the old registry, not failed security assertions.
  It is excluded from the current campaign totals and source validation. The
  final A8/D6 records and execution manifest contain the rerun with the updated
  registry and report four passing cases plus the remaining rotation `xfail`.

Host execution times and browser observations are non-canonical evidence. The
byte-equality check applies to canonical simulated-time result JSON.
