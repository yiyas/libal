#ifndef AL_PUB_H_
#define AL_PUB_H_

#define CHECK_NOMEM_RT(p, rt) if(!(p)) { return rt; }
#define CHECK_NOMEM_DO_RT(p, clause, rt) if(!(p)) { clause; return rt; }

#define CHECK_NULLARG_RT(p, rt) if(!(p)) { return rt; }
#define CHECK_NULLARG2_RT(p1, p2, rt) if(!(p1) || !(p2)) { return rt; }

#endif /* AL_PUB_H_ */
