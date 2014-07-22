/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


      #include "rk_integrator_internal.hpp"
      #include <string>

      const std::string casadi::RKIntegratorInternal::meta_doc=
      "\n"
"\n"
">List of available options\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"|       Id        |      Type       |     Default     |   Description   |\n"
"+=================+=================+=================+=================+\n"
"| ad_mode         | OT_STRING       | \"automatic\"     | How to          |\n"
"|                 |                 |                 | calculate the   |\n"
"|                 |                 |                 | Jacobians.      |\n"
"|                 |                 |                 | (forward: only  |\n"
"|                 |                 |                 | forward         |\n"
"|                 |                 |                 | mode|reverse:   |\n"
"|                 |                 |                 | only adjoint    |\n"
"|                 |                 |                 | mode|automatic: |\n"
"|                 |                 |                 | a heuristic     |\n"
"|                 |                 |                 | decides which   |\n"
"|                 |                 |                 | is more         |\n"
"|                 |                 |                 | appropriate)    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| augmented_optio | OT_DICTIONARY   | GenericType()   | Options to be   |\n"
"| ns              |                 |                 | passed down to  |\n"
"|                 |                 |                 | the augmented   |\n"
"|                 |                 |                 | integrator, if  |\n"
"|                 |                 |                 | one is          |\n"
"|                 |                 |                 | constructed.    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| derivative_gene | OT_DERIVATIVEGE | GenericType()   | Function that   |\n"
"| rator           | NERATOR         |                 | returns a       |\n"
"|                 |                 |                 | derivative      |\n"
"|                 |                 |                 | function given  |\n"
"|                 |                 |                 | a number of     |\n"
"|                 |                 |                 | forward and     |\n"
"|                 |                 |                 | reverse         |\n"
"|                 |                 |                 | directional     |\n"
"|                 |                 |                 | derivative,     |\n"
"|                 |                 |                 | overrides       |\n"
"|                 |                 |                 | internal        |\n"
"|                 |                 |                 | routines. Check |\n"
"|                 |                 |                 | documentation   |\n"
"|                 |                 |                 | of DerivativeGe |\n"
"|                 |                 |                 | nerator.        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| expand_augmente | OT_BOOLEAN      | true            | If DAE callback |\n"
"| d               |                 |                 | functions are   |\n"
"|                 |                 |                 | SXFunction,     |\n"
"|                 |                 |                 | have augmented  |\n"
"|                 |                 |                 | DAE callback    |\n"
"|                 |                 |                 | function also   |\n"
"|                 |                 |                 | be SXFunction.  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| gather_stats    | OT_BOOLEAN      | false           | Flag to         |\n"
"|                 |                 |                 | indicate        |\n"
"|                 |                 |                 | whether         |\n"
"|                 |                 |                 | statistics must |\n"
"|                 |                 |                 | be gathered     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| inputs_check    | OT_BOOLEAN      | true            | Throw           |\n"
"|                 |                 |                 | exceptions when |\n"
"|                 |                 |                 | the numerical   |\n"
"|                 |                 |                 | values of the   |\n"
"|                 |                 |                 | inputs don't    |\n"
"|                 |                 |                 | make sense      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| monitor         | OT_STRINGVECTOR | GenericType()   | Monitors to be  |\n"
"|                 |                 |                 | activated (inpu |\n"
"|                 |                 |                 | ts|outputs)     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| name            | OT_STRING       | \"unnamed_shared | name of the     |\n"
"|                 |                 | _object\"        | object          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| number_of_finit | OT_INTEGER      | 20              | Number of       |\n"
"| e_elements      |                 |                 | finite elements |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| print_stats     | OT_BOOLEAN      | false           | Print out       |\n"
"|                 |                 |                 | statistics      |\n"
"|                 |                 |                 | after           |\n"
"|                 |                 |                 | integration     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| regularity_chec | OT_BOOLEAN      | true            | Throw           |\n"
"| k               |                 |                 | exceptions when |\n"
"|                 |                 |                 | NaN or Inf      |\n"
"|                 |                 |                 | appears during  |\n"
"|                 |                 |                 | evaluation      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| t0              | OT_REAL         | 0               | Beginning of    |\n"
"|                 |                 |                 | the time        |\n"
"|                 |                 |                 | horizon         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tf              | OT_REAL         | 1               | End of the time |\n"
"|                 |                 |                 | horizon         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| user_data       | OT_VOIDPTR      | GenericType()   | A user-defined  |\n"
"|                 |                 |                 | field that can  |\n"
"|                 |                 |                 | be used to      |\n"
"|                 |                 |                 | identify the    |\n"
"|                 |                 |                 | function or     |\n"
"|                 |                 |                 | pass additional |\n"
"|                 |                 |                 | information     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| verbose         | OT_BOOLEAN      | false           | Verbose         |\n"
"|                 |                 |                 | evaluation  for |\n"
"|                 |                 |                 | debugging       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"\n"
"\n"
"\n"
"\n"
;