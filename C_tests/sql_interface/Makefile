trg = dbinterface.out
src = main.c

LDLIBS = -lpthread -ldl -lsqlite3

test_db=db.sqlite

query_statement=SELECT * FROM tasks;

a=$(shell date +%s)
b=$(shell date +%M)
good_test_cmd=INSERT INTO phil (a,b) VALUES ($(a), $(b));

all:$(trg)

$(trg):$(src)
	gcc -o $@ $^ $(LDLIBS)

test:$(trg)
	@echo "This is a query"
	./$(trg) $(test_db) "$(query_statement)"

clean:
	$(RM) $(trg)
