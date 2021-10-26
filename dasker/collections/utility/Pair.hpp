
#ifndef DASKER_COLLECTIONS_UTILITY_PAIR_H
#define DASKER_COLLECTIONS_UTILITY_PAIR_H

namespace dasker::collections::utility
{
    template <typename K, typename V>
    class Pair
    {
        public:
            K key;
            V value;
    };
}

#endif
