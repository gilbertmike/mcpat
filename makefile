TAR = mcpat

.PHONY: dbg opt depend clean clean_dbg clean_opt

all: opt crossbar_opt interconnect_opt

dbg: $(TAR).mk obj_dbg
	@$(MAKE) TAG=dbg -C . -f $(TAR).mk

opt: $(TAR).mk obj_opt
	@$(MAKE) TAG=opt -C . -f $(TAR).mk


crossbar_dbg: crossbar.mk obj_dbg
	@$(MAKE) TAG=dbg -C . -f crossbar.mk

crossbar_opt: crossbar.mk obj_opt
	@$(MAKE) TAG=opt -C . -f crossbar.mk


interconnect_dbg: interconnect.mk obj_dbg
	@$(MAKE) TAG=dbg -C . -f interconnect.mk

interconnect_opt: interconnect.mk obj_opt
	@$(MAKE) TAG=opt -C . -f interconnect.mk


obj_dbg:
	mkdir $@

obj_opt:
	mkdir $@

clean: clean_dbg clean_opt

clean_dbg: obj_dbg
	@$(MAKE) TAG=dbg -C . -f $(TAR).mk clean
	rm -rf $<

clean_opt: obj_opt
	@$(MAKE) TAG=opt -C . -f $(TAR).mk clean
	rm -rf $<

