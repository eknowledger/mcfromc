#pragma once

#define ASSERT(exp)				\
	{							\
		_ASSERT(exp);			\
		LOGCRITC << #exp;		\
	}

#define ASSERT_RETURN_VOID(exp) \
	{						    \
		if(!(exp)){			    \
			_ASSERT(exp);	    \
			return;			    \
		}					    \
	}

#define ASSERT_RETURN(exp,ret) \
	{						   \
		if(!(exp)){		       \
			_ASSERT(exp);	   \
			return ret;		   \
		}				       \
	}

#define ASSERT_LOOP_CONTINUE(exp) \
	{							  \
		if(!(exp)){		          \
			_ASSERT(exp);	      \
			continue;			  \
		}				          \
	}

#define ASSERT_LOOP_BREAK(exp) \
	{						   \
		if(!(exp)){		       \
			_ASSERT(exp);	   \
			break;			   \
		}				       \
	}
