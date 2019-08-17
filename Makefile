CC=gcc
CFLAGS=-w
OUT_DIR=./bin
OUT_FILE=$(lastword $(subst /, , $(subst .c, ,$(FILE)))) 

build: ./src/xmalloc.c ./src/xmalloc.h $(FILE)
	$(CC) $(CFLAGS) ./src/xmalloc.c $(FILE) -o $(OUT_DIR)/$(OUT_FILE) 
	@echo "Executable $(OUT_FILE)placed in $(OUT_DIR) directory"

clean:	
	rm -rf $(OUT_DIR)/*


