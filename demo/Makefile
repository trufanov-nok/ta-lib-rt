
CFLAGS = -I../ta-lib-rt/c/include
LIBS = -L../ta-lib-rt/build/lib -l:libta-lib-rt.a

%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

all: demo

demo: macd_batch.exe macd_rt.exe
	./macd_batch.exe > macd_batch.txt
	./macd_rt.exe    > macd_rt.txt
	(diff macd_batch.txt macd_rt.txt; echo "ok, same!") || (echo "diff failed $$?"; exit 1)

clean:
	$(RM) *.exe

