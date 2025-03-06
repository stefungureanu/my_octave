
gcc=gcc
err=-Wall -Wextra -std=c99
app=my_octave

build: $(app)

my_octave: my_octave.c matrices.c
	$(gcc) $(err) my_octave.c matrices.c -lm -o my_octave

pack:
	zip -FSr 311CA_UngureanuStefan_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(app)

.PHONY: pack clean





