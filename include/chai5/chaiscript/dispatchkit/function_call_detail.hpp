// This file is distributed under the BSD License.
// See "license.txt" for details.
// Copyright 2009-2012, Jonathan Turner (jonathan@emptycrate.com)
// Copyright 2009-2014, Jason Turner (jason@emptycrate.com)
// http://www.chaiscript.com

#ifndef CHAISCRIPT_FUNCTION_CALL_DETAIL_HPP_
#define CHAISCRIPT_FUNCTION_CALL_DETAIL_HPP_

#include <string>
#include <vector>
#include "proxy_functions.hpp"

namespace chaiscript
{
  namespace dispatch
  {
    namespace detail
    {

      /**
       * Internal helper class for handling the return
       * value of a build_function_caller
       */
      template<typename Ret>
        struct Function_Caller_Ret
        {
          static Ret call(const std::vector<Const_Proxy_Function> &t_funcs, 
              const std::vector<Boxed_Value> &params, const Dynamic_Cast_Conversions &t_conversions)
          {
            return boxed_cast<Ret>(dispatch::dispatch(t_funcs, params, t_conversions));
          }
        };

      /**
       * Specialization for void return types
       */
      template<>
        struct Function_Caller_Ret<void>
        {
          static void call(const std::vector<Const_Proxy_Function> &t_funcs, 
              const std::vector<Boxed_Value> &params, const Dynamic_Cast_Conversions &t_conversions)
          {
            dispatch::dispatch(t_funcs, params, t_conversions);
          }
        };

      /**
       * used internally for unwrapping a function call's types
       */
      template<typename Ret, typename ... Param>
        struct Build_Function_Caller_Helper
        {
          Build_Function_Caller_Helper(const std::vector<Const_Proxy_Function> &t_funcs, const Dynamic_Cast_Conversions &t_conversions)
            : m_funcs(t_funcs),
              m_conversions(t_conversions)
          {
          }

          Ret operator()(Param...param)
          {
            return Function_Caller_Ret<Ret>::call(m_funcs, { 
(std::is_reference<Param>::value&&!(std::is_same<chaiscript::Boxed_Value, typename std::remove_const<typename std::remove_reference<Param>::type>::type>::value))?Boxed_Value(std::ref(param)):Boxed_Value(param)... 
          }, m_conversions
          
          );

          }

          std::vector<Const_Proxy_Function> m_funcs;
          Dynamic_Cast_Conversions m_conversions;
        };



      template<typename Ret, typename ... Params>
        std::function<Ret (Params...)> build_function_caller_helper(Ret (Params...), const std::vector<Const_Proxy_Function> &funcs, const Dynamic_Cast_Conversions *t_conversions)
        {
          if (funcs.size() == 1)
          {
            std::shared_ptr<const Proxy_Function_Impl<Ret (Params...)>> pfi = 
              std::dynamic_pointer_cast<const Proxy_Function_Impl<Ret (Params...)> >
                (funcs[0]);

            if (pfi)
            {
              return pfi->internal_function();
            } 
            // looks like this either wasn't a Proxy_Function_Impl or the types didn't match
            // we cannot make any other guesses or assumptions really, so continuing
          }

          return std::function<Ret (Params...)>(Build_Function_Caller_Helper<Ret, Params...>(funcs, t_conversions?*t_conversions:Dynamic_Cast_Conversions()));
        }
    }
  }
}

#endif

