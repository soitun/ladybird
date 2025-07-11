/*
 * Copyright (c) 2021, Idan Horowitz <idan.horowitz@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibJS/Runtime/NativeFunction.h>

namespace JS {

class JS_API SetConstructor final : public NativeFunction {
    JS_OBJECT(SetConstructor, NativeFunction);
    GC_DECLARE_ALLOCATOR(SetConstructor);

public:
    virtual void initialize(Realm&) override;
    virtual ~SetConstructor() override = default;

    virtual ThrowCompletionOr<Value> call() override;
    virtual ThrowCompletionOr<GC::Ref<Object>> construct(FunctionObject&) override;

private:
    explicit SetConstructor(Realm&);

    virtual bool has_constructor() const override { return true; }

    JS_DECLARE_NATIVE_FUNCTION(symbol_species_getter);
};

}
