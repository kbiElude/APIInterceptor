/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "OpenGL/types.h"

OpenGL::DispatchTable::DispatchTable()
{
    memset(this,
           0,
           sizeof(*this) );
}
