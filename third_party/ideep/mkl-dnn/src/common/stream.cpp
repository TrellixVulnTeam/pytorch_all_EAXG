/*******************************************************************************
* Copyright 2016-2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <assert.h>
#include "dnnl.h"

#include "c_types_map.hpp"
#include "engine.hpp"
#include "stream.hpp"
#include "utils.hpp"

using namespace dnnl::impl;
using namespace dnnl::impl::status;
using namespace dnnl::impl::utils;

/* API */

status_t dnnl_stream_create_v2(stream_t **stream, engine_t *engine,
        unsigned flags, const stream_attr_t *attr) {
    bool args_ok = true && !utils::any_null(stream, engine)
            && flags == stream_flags::default_flags;
    if (!args_ok) return invalid_arguments;

    return engine->create_stream(stream, flags, attr);
}

status_t dnnl_stream_create(
        stream_t **stream, engine_t *engine, unsigned flags) {
    return dnnl_stream_create_v2(stream, engine, flags, nullptr);
}

status_t dnnl_stream_get_engine(const stream_t *stream, engine_t **engine) {
    if (any_null(stream, engine)) return invalid_arguments;
    *engine = stream->engine();
    return success;
}

status_t dnnl_stream_wait(stream_t *stream) {
    bool args_ok = !any_null(stream);
    if (!args_ok) return invalid_arguments;

    return stream->wait();
}

status_t dnnl_stream_destroy(stream_t *stream) {
    delete stream;
    return success;
}

// vim: et ts=4 sw=4 cindent cino+=l0,\:4,N-s
