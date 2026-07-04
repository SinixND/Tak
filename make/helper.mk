ifndef __HELPER_MK
__HELPER_MK := 1

### Helper functions
fn_rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call fn_rwildcard,$d,$2)$(filter $(subst *,%,$2),$d)) # Trailing space required
fn_files     = $(sort $(call fn_rwildcard,$1,$2))
fn_dirs      = $(sort $(dir $(call fn_rwildcard,$1,*)))

endif
