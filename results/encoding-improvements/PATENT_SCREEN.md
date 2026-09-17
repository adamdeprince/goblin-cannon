# Simulated channel — implementation patent screen

Review date: 2026-09-17. Scope used: US publications and discovered international
families. This is a
public-record engineering screen, not a legal freedom-to-operate opinion. No
claim of worldwide absence of patents is made. Search results and database status
labels can omit national changes, continuations, reinstatement and unpublished
applications. The existing repository was not subjected to a whole-product audit.

## Simulated channel — included implementations

| Candidate | Concrete implementation boundary | Historical technical basis |
| --- | --- | --- |
| Soft decoding | Exhaustive, fixed-constellation Euclidean max-log bit metrics; known-pilot mean-square residual; ordinary Viterbi branch costs. No learned constellation or demapper decision boundaries. | [Forney, Viterbi history (2005)](https://arxiv.org/abs/cs/0504020), [MIT soft-decision lectures (2005)](https://ocw.mit.edu/courses/6-451-principles-of-digital-communication-ii-spring-2005/video_galleries/video-lectures/) |
| Stronger convolutional BPSK | K=9 rate 1/2, octal 753/561; K=9 rate 1/3, 557/663/711. Ordinary continuous trellis, no turbo iteration, tail-biting or novel pruning. | [2004 physical-layer specification extract, pp. 2–4](https://cioffi-group.stanford.edu/ee379b/class_reader/3G_turbocode_interleaver.pdf) |
| Walsh spreading | Three bits select a row of the ordinary 8×8 Hadamard matrix; chips use BPSK; direct correlation-bank decoder. | [MIT orthogonal-signalling lecture](https://ocw.mit.edu/courses/6-450-principles-of-digital-communications-i-fall-2006/2b65eb863b322f3e1077210922162509_cfL8blVkE1E.pdf); the published patent below itself describes earlier Walsh use |
| Noncoherent FSK | Conventional orthogonal 4/8-tone bank, square-law energy detection, known tone preamble and convolutional header. No carrier tracker. | [NTIA TR 00-371](https://its.ntia.gov/publications/download/00-371_ocr.pdf), [NTIA measurements](https://its.ntia.gov/publications/details?pub=3358) |
| Frequency diversity | Duplicate a BPSK waveform in two separated audio subbands; split fixed total power; combine independently obtained bit scores at matching positions. No space-time/matrix code, antenna precoding or adaptive resource allocation. | [Watterson, NTIA TR 79-29](https://its.ntia.gov/publications/details?pub=1975) |
| Interleaving | Fixed rectangular row-write/column-read permutation. No adaptive interleaver or turbo-specific address construction. | [NTIA TR 00-371](https://its.ntia.gov/publications/download/00-371_ocr.pdf) |
| Short block code | Conventional primitive BCH(63,45,7), shortened to (58,40,7), polynomial arithmetic, Berlekamp–Massey and Chien search. | [2003 historical account of BCH](https://www.microsoft.com/en-us/research/wp-content/uploads/2003/09/resonance-sep2003.pdf), [earlier BCH patent record](https://patents.google.com/patent/EP0431576B1/en) (listed expired by lifetime) |

These historical publications and the deliberately limited implementations support
including these experiments; they do not prove non-infringement. A relevant patent
must cover the implemented combination, not merely mention FSK, Walsh, BCH or LLRs.

## Simulated channel — excluded or unresolved designs

| Record / family | Public-record observation | Exclusion |
| --- | --- | --- |
| [US8059693B2](https://patents.google.com/patent/US8059693B2/en), [EP2146453B1](https://patents.google.com/patent/EP2146453B1/en), IL199813 | Discovered family includes active listings; 2008 priority. The EP independent claims combine Walsh transforms, cyclic extension and frequency modulation, with implementation limitations. | No constant-radius orthogonal Walsh (CROW), FM of Walsh transform outputs, or corresponding receiver. Plain historical Walsh rows are a different implementation. |
| [US10027423B1](https://patents.google.com/patent/US10027423B1/en) | 2016 filing. Claim 1 includes updating the constellation together with demapping and corrected noise estimation. Current enforceability was not independently established. | No learned constellation points, adaptive decision regions, hard-decision noise correction factors, or restricted candidate-set demapper. |
| [US11942964B2](https://patents.google.com/patent/US11942964B2/en) | Listed active with 2037 expiry; concerns describing lifted LDPC codes. | Specialized short LDPC constructions, supplied NASA/CCSDS matrices and optimized decoders remain excluded pending a construction-specific review. This does not assert that all LDPC codes are patented. BCH implements the short-block experiment. |
| [US8656245B2](https://patents.google.com/patent/US8656245B2/en) | Listed expired for fees, with a later adjusted term; a fee lapse is not used as clearance. | No LDPC error-floor mitigation from this design. |
| [US20240214156A1](https://patents.google.com/patent/US20240214156A1/en) | Listed pending; matrix-based noncoherent transmit diversity. | No codebook/matrix/space-time diversity from this application. |
| 2024 Walsh-constrained orthogonal approximate-message-passing receiver | Published paper is not a patent clearance; related coverage unresolved. | No OAMP equalizer or algorithm from that paper. Existing RLS remains in use. |

Patent age alone is insufficient: the [USPTO](https://www.uspto.gov/web/offices/pac/mpep/s2701.html)
describes term adjustments and exceptions. Maintenance status could not be
independently checked through the account-gated [USPTO storefront](https://fees.uspto.gov/).
The exclusion policy therefore includes unresolved modern implementations instead
of treating a database's fee-lapse label as permission.

## Simulated channel — reproducible search scope

Queries included: soft-decision/Viterbi max-log demapper patents; adaptive demapper
noise variance; Walsh HF modulation and equalization; short LDPC and protograph
families; noncoherent FSK; frequency diversity; BCH decoder patents. The linked
publications/claims above are the implementation decisions' evidence. An absence
of further search hits is not recorded as a finding of no patent coverage.
