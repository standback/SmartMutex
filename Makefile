DIRS = src 
All:
	set -e;	for dir in $(DIRS);do  make  -C $$dir;done
test:
	for dir in $(DIRS);do make test -C $$dir ;done
clean:
	for dir in $(DIRS);do make clean -C $$dir ;done
	
