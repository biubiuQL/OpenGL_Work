.PHONY: run
run:
	@cmake -S . -B build
	@cmake --build build
	@./build/main.exe