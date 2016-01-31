#!############################################################################
#!
#! This is a tmake template for creating a makefile that invokes make in
#! sub directories - for Unix.
#!
#${
    Project('MAKEFILE') || Project('MAKEFILE = Makefile');
    Project('TMAKE') || Project('TMAKE = tmake');
#$}
#!
#! Makefile for building targets in sub directories.
#! Generated by tmake at #$ Now();
#!     Project: #$ Expand("PROJECT");
#!    Template: #$ Expand("TEMPLATE");
#!############################################################################
#!TMAKE =   #$ Expand("TMAKE");
MAKEFILE        = #$ Expand("MAKEFILE");
#$ DisableOutput() unless Project("MAKE_PARALLEL");
LEAFSUBDIRS     = #$ ExpandGlue("LEAFSUBDIRS", "", " \\\n\t\t", "\n");
NODESUBDIRS     = #$ ExpandGlue("NODESUBDIRS", "", " \\\n\t\t", "\n");
#!SUBDIRS         = $(LEAFSUBDIRS) $(NODESUBDIRS)
MAKE_PARALLEL   = #$ Expand("MAKE_PARALLEL");
#$ EnableOutput() unless Project("MAKE_PARALLEL");
#!$ DisableOutput() if Project("MAKE_PARALLEL");
SUBDIRS         = #$ ExpandGlue("SUBDIRS", "", " \\\n\t\t", "\n");
#!$ EnableOutput() if Project("MAKE_PARALLEL");
all: $(SUBDIRS)

#$ DisableOutput() unless Project("LEAFSUBDIRS") && Project("MAKE_PARALLEL");
$(LEAFSUBDIRS): force
	$(MAKE) -C $@ $(MAKE_PARALLEL) -f $(MAKEFILE) #$ $text .= '$(MAKECMDGOALS)' if Project("PARALLEL_SUBDIRS");
#$ EnableOutput() unless Project("LEAFSUBDIRS") && Project("MAKE_PARALLEL");
#$ DisableOutput() unless Project("NODESUBDIRS") && Project("MAKE_PARALLEL");
$(NODESUBDIRS): force
	$(MAKE) -C $@ -f $(MAKEFILE) #$ $text .= '$(MAKECMDGOALS)' if Project("PARALLEL_SUBDIRS");
#$ EnableOutput() unless Project("NODESUBDIRS") && Project("MAKE_PARALLEL");
#$ DisableOutput() if Project("MAKE_PARALLEL");
$(SUBDIRS):
	$(MAKE) -C $@ -f $(MAKEFILE) #$ $text .= '$(MAKECMDGOALS)' if Project("PARALLEL_SUBDIRS");
#$ EnableOutput() if Project("MAKE_PARALLEL");

CONFIGURE_TARGET = #$ $text = "configure" unless Project("AUTOCONF_T_INCLUDED");
CLEANFILES       = #$ Expand("CLEANFILES");
CLEANDIRS        = #$ Expand("CLEANDIRS");

#$ DisableOutput() if Project("PARALLEL_SUBDIRS");
install test pkg install_only $(CONFIGURE_TARGET):
	for i in $(SUBDIRS); do ( if [ -d $$i ]; then $(MAKE) -C $$i -f $(MAKEFILE) $@; fi; ) || exit $$?; done
#$ EnableOutput() if Project("PARALLEL_SUBDIRS");
#$ DisableOutput() unless Project("PARALLEL_SUBDIRS");
install test pkg install_only $(CONFIGURE_TARGET): $(SUBDIRS)
#$ EnableOutput() unless Project("PARALLEL_SUBDIRS");

clean:
#$ Project("CLEANFILES") and $text = "\trm -f \$(CLEANFILES)";
#$ Project("CLEANDIRS") and $text = "\trm -fr \$(CLEANDIRS)";
	for i in $(SUBDIRS); do ( if [ -d $$i ]; then $(MAKE) -C $$i -f $(MAKEFILE) $@; fi; ) || exit $$?; done

.PHONY: clean install test pkg install_only all $(SUBDIRS) $(CONFIGURE_TARGET)