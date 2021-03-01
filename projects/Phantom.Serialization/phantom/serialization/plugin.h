// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#pragma once

//==========================================================
// Macro for export / import
//==========================================================

#if !defined(PHANTOM_STATIC_LINK_PHANTOM_SERIALIZATION)
#    if defined(PHANTOM_LIB_PHANTOM_SERIALIZATION)
#        define PHANTOM_EXPORT_PHANTOM_SERIALIZATION PHANTOM_VISIBILITY_EXPORT
#    else
#        define PHANTOM_EXPORT_PHANTOM_SERIALIZATION PHANTOM_VISIBILITY_IMPORT
#    endif

#else // defined(PHANTOM_STATIC_LINK_PHANTOM_SERIALIZATION)
#    define PHANTOM_EXPORT_PHANTOM_SERIALIZATION

#endif // !defined(PHANTOM_STATIC_LINK_PHANTOM_SERIALIZATION)

//==========================================================
// Deactivation of warning 4251
// "T1 needs a DLL interface to be used by T2 class clients"
//==========================================================

#ifdef _MSC_VER
#    pragma warning(disable : 4251)
#endif
