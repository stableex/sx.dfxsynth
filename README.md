# **`SX.DFXSynth`**

> Interface for interacting with `dfxxexchange` smart contract


## Quickstart

```c++
#include <sx.dfxsynth/dfxsynth.hpp>

// user input
const extended_asset quantity = extended_asset{ asset{ 100000000, symbol{"YEOS", 8} }, "dfxsynthetic"_n};
const symbol sym = symbol{ "DFG", 4 };

// calculate out price
const asset out = dfxsynth::get_amount_out( quantity, sym );
// => "5.6500 DFG"
```
