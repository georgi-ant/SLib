/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_CORE_MEMORY
#define CHECKHEADER_SLIB_CORE_MEMORY

#include "definition.h"

#include "array.h"
#include "queue.h"

namespace slib
{

	class MemoryData;
	
	class CMemory : public CArray<sl_uint8>
	{
		SLIB_DECLARE_OBJECT

	protected:
		CMemory();

	public:
		CMemory(sl_size count);

		CMemory(const void* data, sl_size size);

		CMemory(const void* data, sl_size size, Referable* refer);

		~CMemory();

	public:
		static CMemory* create(sl_size size);

		static CMemory* create(const void* data, sl_size size);

		static CMemory* createStatic(const void* data, sl_size size, Referable* refer);
	
	public:
		CMemory* sub(sl_size start, sl_size size = SLIB_SIZE_MAX);

		CMemory* duplicate() const;

	};
	
	class Memory;
	
	template <>
	class SLIB_EXPORT Atomic<Memory>
	{
	public:
		AtomicRef<CMemory> ref;
		SLIB_ATOMIC_REF_WRAPPER(CMemory)

	public:
		sl_size getSize() const;

		sl_bool isEmpty() const;

		sl_bool isNotEmpty() const;

		Memory sub(sl_size start, sl_size count = SLIB_SIZE_MAX) const;

		sl_size read(sl_size startSource, sl_size len, void* bufDst) const;

		sl_size write(sl_size startTarget, sl_size len, const void* bufSrc) const;

		sl_size copy(sl_size startTarget, const Memory& source, sl_size startSource = 0, sl_size len = SLIB_SIZE_MAX) const;

		sl_size copy(const Memory& source, sl_size startSource = 0, sl_size len = SLIB_SIZE_MAX) const;

		Memory duplicate() const;

		sl_bool getData(MemoryData& data) const;

	};
	
	class SLIB_EXPORT Memory
	{
	public:
		Ref<CMemory> ref;
		SLIB_REF_WRAPPER(Memory, CMemory)

	public:
		static Memory create(sl_size count);

		static Memory create(const void* buf, sl_size size);

		static Memory createStatic(const void* buf, sl_size size);

		static Memory createStatic(const void* buf, sl_size size, Referable* refer);

	public:
		void* getData() const;

		sl_size getSize() const;

		sl_bool isEmpty() const;

		sl_bool isNotEmpty() const;

		Memory sub(sl_size start, sl_size size = SLIB_SIZE_MAX) const;

		sl_size read(sl_size startSource, sl_size size, void* bufDst) const;

		sl_size write(sl_size startTarget, sl_size size, const void* bufSrc) const;

		sl_size copy(sl_size startTarget, const Memory& source, sl_size startSource = 0, sl_size size = SLIB_SIZE_MAX) const;

		sl_size copy(const Memory& source, sl_size start = 0, sl_size size = SLIB_SIZE_MAX) const;

		Memory duplicate() const;

		sl_bool getData(MemoryData& data) const;

	};
	
	typedef Atomic<Memory> AtomicMemory;
	
	class SLIB_EXPORT MemoryData
	{
	public:
		void* data;
		sl_size size;
		Ref<Referable> refer;

	public:
		MemoryData();
		
		MemoryData(const MemoryData& other);

		~MemoryData();

	public:
		Memory getMemory() const;

		Memory sub(sl_size start, sl_size size = SLIB_SIZE_MAX) const;

	};
	
	
	// MemoryBuffer is not thread-safe
	class SLIB_EXPORT MemoryBuffer : public Object
	{
	public:
		MemoryBuffer();

		~MemoryBuffer();
	
	public:
		sl_size getSize() const;

		sl_bool add(const MemoryData& mem);
	
		sl_bool add(const Memory& mem);

		sl_bool addStatic(const void* buf, sl_size size);
	
		void link(MemoryBuffer& buf);
	
		void clear();
	
		Memory merge() const;
	
	protected:
		LinkedQueue<MemoryData> m_queue;
		sl_size m_size;

	};
	
	class SLIB_EXPORT MemoryQueue : public Object
	{
	public:
		MemoryQueue();

		~MemoryQueue();
	
	public:
		sl_size getSize() const;
		
		sl_bool add_NoLock(const MemoryData& mem);
		
		sl_bool add(const MemoryData& mem);
		
		sl_bool add_NoLock(const Memory& mem);
		
		sl_bool add(const Memory& mem);
		
		sl_bool addStatic_NoLock(const void* buf, sl_size size);
		
		sl_bool addStatic(const void* buf, sl_size size);
		
		void link_NoLock(MemoryQueue& buf);
		
		void link(MemoryQueue& buf);
		
		void clear_NoLock();
		
		void clear();

		sl_bool pop_NoLock(MemoryData& data);
		
		sl_bool pop(MemoryData& data);
		
		sl_size pop_NoLock(void* buf, sl_size size);
	
		sl_size pop(void* buf, sl_size size);
		
		Memory merge_NoLock() const;
	
		Memory merge() const;
	
	private:
		LinkedQueue<MemoryData> m_queue;
		sl_size m_size;
		MemoryData m_memCurrent;
		sl_size m_posCurrent;

	};

}

#endif
