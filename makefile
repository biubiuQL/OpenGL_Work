.PHONY: run

mkdir:
	@$(shell mkdir -p build) 

clean:mkdir
	@del /s /q /f build\* && for /d %%x in (build\*) do rmdir /s /q "%%x"

compile:clean
	@cmake -S . -B build
	@cmake --build build

run:compile
	@./build/main.exe

