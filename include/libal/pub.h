/**
 * Copyright (c) 2015 - 2021 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef AL_PUB_H_
#define AL_PUB_H_

#include <stdio.h>

#ifdef __GNUC__
#  define UNUSED(x) UNUSED_##x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#define CHECK_NOMEM_RT(p, rt) if(!(p)) { return rt; }
#define CHECK_NOMEM_DO_RT(p, clause, rt) if(!(p)) { clause; return rt; }
#define CHECK_NOMEM_GOTO(p, label) if(!(p)) { goto label; }
#define CHECK_NOMEM_DO_GOTO(p, clause, label) if(!(p)) { clause; goto label; }

#define CHECK_NULLARG_RT(p, rt) if(!(p)) { return rt; }
#define CHECK_NULLARG_GOTO(p, label) if(!(p)) { goto label; }
#define CHECK_NULLARG2_RT(p1, p2, rt) if(!(p1) || !(p2)) { return rt; }
#define CHECK_NULLARG2_GOTO(p1, p2, label) if(!(p1) || !(p2)) { goto label; }
#define CHECK_NULLARG3_RT(p1, p2, p3, rt) if(!(p1) || !(p2) || !(p3)) { return rt; }

#define CHECK_INTERR_RT(cond, rt) if((cond)) { return rt; }
#define CHECK_INTERR_DO_RT(cond, clause, rt) if((cond)) { clause; return rt; }
#define CHECK_INTERR_GOTO(cond, label) if((cond)) { goto label; }
#define CHECK_INTERR_DO_GOTO(cond, clause, label) if((cond)) { clause; goto label; }

#endif /* AL_PUB_H_ */
