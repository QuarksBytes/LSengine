print("Lua is calling C++...")

local response = cpp_callback("Hello from Lua!")
print("C++ responded:", response)
