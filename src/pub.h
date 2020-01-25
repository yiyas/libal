/**
 * Copyright (c) 2015 - 2017 YIYAS
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

#define CHECK_NOMEM_RT(p, rt) if(!(p)) { return rt; }
#define CHECK_NOMEM_DO_RT(p, clause, rt) if(!(p)) { clause; return rt; }

#define CHECK_NULLARG_RT(p, rt) if(!(p)) { return rt; }
#define CHECK_NULLARG2_RT(p1, p2, rt) if(!(p1) || !(p2)) { return rt; }

#define CHECK_INTERR_RT(p, rt) if((p)) { return rt; }
#define CHECK_INTERR_DO_RT(p, clause, rt) if((p)) { clause; return rt; }

#endif /* AL_PUB_H_ */
