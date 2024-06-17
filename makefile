.PHONY: run

mkdir:
	@$(shell mkdir -p build) 

clean:mkdir
	@del /s /q /f build\* && for /d %%x in (build\*) do rmdir /s /q "%%x"

run:clean
	@cmake -S . -B build
	@cmake --build build
	@./build/main.exe

