

function adder(pins) -- A0 A1 B0 B1 S0 S1 Cin Cout
    pins["a0"] = 1
    pins["a1"] = 1
    forward({"a0","a1"})

    pins["b0"] =0
    pins["b1"] = 0
    forward({"b0","b1"})
    
end

