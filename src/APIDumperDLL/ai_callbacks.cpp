/* API Dumper (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
 #include "Common/callbacks.h"
 #include "APIDumper.h"

static APIDumperUniquePtr g_instance_ptr;


void on_api_interceptor_removed()
{
    g_instance_ptr.reset();
}

void on_api_interceptor_injected()
{
    g_instance_ptr = APIDumper::create();
}