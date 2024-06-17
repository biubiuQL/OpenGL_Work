.PHONY: run
run:clean
	@cmake -S . -B build
	@cmake --build build
	@./build/main.exe


clean:
	@del /s /q /f build\* && for /d %%x in (build\*) do rmdir /s /q "%%x"