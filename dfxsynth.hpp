#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <sx.usdxsynth/usdxsynth.hpp>

namespace dfxsynth {

    using namespace eosio;

    // reference
    const name id = "dfxsynth"_n;
    const name code = "dfxxexchange"_n;
    const std::string description = "DFX Synth";
    const name token_code = "dfxsynthetic"_n;
    const symbol BASE_SYM = symbol {"DFG", 4};

    static uint64_t get_fee() {
        return 30;
    }
    /**
     * ## STATIC `get_amount_out`
     *
     * Return conversion amount
     *
     * ### params
     *
     * - `{asset} in` - in asset
     * - `{symbol} sym_out` - out symbol
     *
     * ### returns
     *
     * - `{asset}` - asset
     *
     * ### example
     *
     * ```c++
     * const asset in = {1'00000000, symbol{"YEOS",8}};
     * const symbol sym_out = {"DFG", 4}
     *
     * const auto out = dfxsynth::get_amount_out( in, sym_out );
     * // out => "5.3000 DFG"
     * ```
     */
    static asset get_amount_out(const asset in, const symbol sym_out )
    {
        check(sym_out == BASE_SYM || in.symbol == BASE_SYM, "dfxsynth: only DFG can be used to mint");

        usdxsynth::iprices iprices_tbl( usdxsynth::code, usdxsynth::code.value );
        auto ysym = sym_out == BASE_SYM ? in.symbol : sym_out;
        std::string str = ysym.code().to_string();
        str[0] = 'X';
        symbol xsym {str, 8};
        const auto token  = iprices_tbl.get(xsym.code().raw(), "dfxsynth: wrong Y token");

        double out_amount = sym_out == BASE_SYM ? in.amount * token.index_price : in.amount / token.index_price;
        out_amount = out_amount * (10000 - get_fee()) / 10000;

        return { static_cast<int64_t>(out_amount  / pow(10, in.symbol.precision() - sym_out.precision())), sym_out };
    }


}