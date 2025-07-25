/*
 * Copyright (c) 2022, Andreas Kling <andreas@ladybird.org>
 * Copyright (c) 2022, Sam Atkins <atkinssj@serenityos.org>
 * Copyright (c) 2024, Kenneth Myhra <kennethmyhra@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/DOMPointReadOnlyPrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Geometry/DOMMatrix.h>
#include <LibWeb/Geometry/DOMPointReadOnly.h>
#include <LibWeb/HTML/StructuredSerialize.h>
#include <LibWeb/WebIDL/ExceptionOr.h>

namespace Web::Geometry {

GC_DEFINE_ALLOCATOR(DOMPointReadOnly);

GC::Ref<DOMPointReadOnly> DOMPointReadOnly::construct_impl(JS::Realm& realm, double x, double y, double z, double w)
{
    return realm.create<DOMPointReadOnly>(realm, x, y, z, w);
}

GC::Ref<DOMPointReadOnly> DOMPointReadOnly::create(JS::Realm& realm)
{
    return realm.create<DOMPointReadOnly>(realm);
}

DOMPointReadOnly::DOMPointReadOnly(JS::Realm& realm, double x, double y, double z, double w)
    : PlatformObject(realm)
    , m_x(x)
    , m_y(y)
    , m_z(z)
    , m_w(w)
{
}

DOMPointReadOnly::DOMPointReadOnly(JS::Realm& realm)
    : PlatformObject(realm)
{
}

// https://drafts.fxtf.org/geometry/#dom-dompointreadonly-frompoint
GC::Ref<DOMPointReadOnly> DOMPointReadOnly::from_point(JS::VM& vm, DOMPointInit const& other)
{
    // The fromPoint(other) static method on DOMPointReadOnly must create a DOMPointReadOnly from the dictionary other.
    return construct_impl(*vm.current_realm(), other.x, other.y, other.z, other.w);
}

DOMPointReadOnly::~DOMPointReadOnly() = default;

// https://drafts.fxtf.org/geometry/#dom-dompointreadonly-matrixtransform
WebIDL::ExceptionOr<GC::Ref<DOMPoint>> DOMPointReadOnly::matrix_transform(DOMMatrixInit& matrix) const
{
    // 1. Let matrixObject be the result of invoking create a DOMMatrix from the dictionary matrix.
    auto matrix_object = TRY(DOMMatrix::create_from_dom_matrix_init(realm(), matrix));

    // 2. Return the result of invoking transform a point with a matrix, given the current point and matrixObject. The current point does not get modified.
    return matrix_object->transform_point(*this);
}

void DOMPointReadOnly::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(DOMPointReadOnly);
    Base::initialize(realm);
}

WebIDL::ExceptionOr<void> DOMPointReadOnly::serialization_steps(HTML::TransferDataEncoder& serialized, bool, HTML::SerializationMemory&)
{
    // 1. Set serialized.[[X]] to value’s x coordinate.
    serialized.encode(m_x);

    // 2. Set serialized.[[Y]] to value’s y coordinate.
    serialized.encode(m_y);

    // 3. Set serialized.[[Z]] to value’s z coordinate.
    serialized.encode(m_z);

    // 4. Set serialized.[[W]] to value’s w coordinate.
    serialized.encode(m_w);

    return {};
}

WebIDL::ExceptionOr<void> DOMPointReadOnly::deserialization_steps(HTML::TransferDataDecoder& serialized, HTML::DeserializationMemory&)
{
    // 1. Set value’s x coordinate to serialized.[[X]].
    m_x = serialized.decode<double>();

    // 2. Set value’s y coordinate to serialized.[[Y]].
    m_y = serialized.decode<double>();

    // 3. Set value’s z coordinate to serialized.[[Z]].
    m_z = serialized.decode<double>();

    // 4. Set value’s w coordinate to serialized.[[W]].
    m_w = serialized.decode<double>();

    return {};
}

}
