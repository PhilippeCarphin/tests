CFLAGS += -Wall -g -std=gnu99
# Even if they're not needed for the particular test
LDFLAGS += -lm -ldl

%:%.c
	gcc $(CFLAGS) $(LDFLAGS) $@.c -o $@
	./$@

clean:
	find . -maxdepth 1 -perm -a=x -type f -exec echo {} \; -exec rm {} \;

