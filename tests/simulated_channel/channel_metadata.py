"""Channel quantities and backwards-compatible names for recorded simulations."""
from __future__ import annotations

import warnings

DOPPLER_SHIFT_DEFINITION = (
    "Doppler shift: a mean frequency offset of the received signal relative to the "
    "transmitted carrier; a translation of the whole spectrum. Hz. Caused by bulk "
    "ionospheric motion plus transmitter/receiver LO error. Removing it is a "
    "frequency-tracking (AFC) problem."
)
DOPPLER_SPREAD_DEFINITION = (
    "Doppler spread: the width of the Doppler power spectrum of a propagation path, "
    "i.e. the fading rate. Hz. In the Watterson / ITU-R F.1487 model it is the width "
    "of the Gaussian spectrum applied to each tap. It is not an offset and no AFC "
    "removes it; it appears as fast fading and phase rotation the equalizer must "
    "track. 30 Hz means a coherence time on the order of tens of milliseconds."
)
SPREAD_CONVENTION = "Gaussian spectrum per tap; Doppler spread is the 2-sigma width, not sigma."
LEGACY_CONVENTION = "2*sigma of Gaussian power spectrum; zero path carrier shifts"
PARAMETER_ALIASES = {
    "doppler": "doppler_spread_hz",
    "doppler_hz": "doppler_spread_hz",
    "itu_doppler_duration_s": "itu_doppler_spread_duration_s",
}


def normalize_parameters(parameters, *, warn=True):
    """Return canonical metadata without mutating historical records or metrics."""
    result = dict(parameters)
    for old, new in PARAMETER_ALIASES.items():
        if old not in result:
            continue
        value = result.pop(old)
        if new in result and result[new] != value:
            raise ValueError(f"Conflicting channel parameters: {old} and {new}")
        result[new] = value
        if warn:
            warnings.warn(f"{old} is deprecated; use {new}", DeprecationWarning, stacklevel=2)
    if "doppler_definition" in result:
        legacy = result.pop("doppler_definition")
        if legacy != LEGACY_CONVENTION:
            raise ValueError(f"Unrecognized legacy Doppler spread convention: {legacy!r}")
        result.setdefault("doppler_spread_definition", DOPPLER_SPREAD_DEFINITION)
        result.setdefault("doppler_spread_convention", SPREAD_CONVENTION)
        result.setdefault("doppler_shift_hz", [0.0, 0.0] if result.get("channel_model") == "watterson" else None)
        if warn:
            warnings.warn("doppler_definition is deprecated; use doppler_spread_definition and doppler_spread_convention",
                          DeprecationWarning, stacklevel=2)
    return result


def normalize_record(record, *, warn=True):
    result = dict(record)
    result["parameters"] = normalize_parameters(record["parameters"], warn=warn)
    return result
