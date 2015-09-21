//
// Created by Dusan Klinec on 18.09.15.
//

#ifndef OPENSIPS_1_11_2_TLS_MESSAGETHREADMANAGER_H
#define OPENSIPS_1_11_2_TLS_MESSAGETHREADMANAGER_H

#include <memory>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>
#include <unordered_map>
#include "logic.h"
#include "MessageThreadElement.hpp"
#include "MessageThreadMap.hpp"
#include "SenderJobQueue.hpp"

namespace bip = boost::interprocess;

// Main allocator, will be used after rebind call to allocate list elements.
typedef SipsSHMAllocator<MessageListElement> MainAllocator;

// Main mesage thread manager.
class MessageThreadManager {
private:
    // Global interprocess mutex, structure wide for fetching records.
    boost::interprocess::interprocess_mutex mutex;

    // Linked list of all records with NONE status => cached in LRU fashion, if cache is too big
    // these records are recycled in LRU policy.
    MessageThreadCache * threadCache;

    // Main allocator to be used in construction of a message list elements and message thread elements.
    MainAllocator alloc;

    // Unordered hash map of the message thread elements.
    // Main structure for organizing message threads.
    MessageThreadMap threadMap;

    // Sender job queue, HSM allocated.
    SenderJobQueue jobQueue;

public:

    // TODO: take an allocator, rebind it to desired type in order to allocate memory in SHM.
    MessageThreadManager(const MainAllocator &alloc) :
            alloc{alloc},
            threadCache{NULL},
            jobQueue{std::allocator_traits<decltype(alloc)>::rebind_alloc<SenderQueueJob> allocator}
    {


    }



};


#endif //OPENSIPS_1_11_2_TLS_MESSAGETHREADMANAGER_H
