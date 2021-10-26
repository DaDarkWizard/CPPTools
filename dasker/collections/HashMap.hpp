#include "Pair.hpp"
#include <functional>
#include <iostream>
#include "ArrayList.hpp"

#ifndef DASKER_COLLECTIONS_HASHMAP_H
#define DASKER_COLLECTIONS_HASHMAP_H

namespace dasker::collections
{
    template <typename K, typename V>
    class HashMap
    {
        private:
            int mapSize;
            int maxCollisions;
            utility::Pair<K, V>** map;
            std::hash<K> hashK;
            void doubleSize();
            int elementCount;
        public:
            HashMap();
            ~HashMap();
            bool contains(K key);
            V get(K key);
            int size();
            void put(K key, V value);
            ArrayList<K> keyList();
    };
    
    template <typename K, typename V>
    HashMap<K, V>::HashMap()
    {
        mapSize = 10;
        maxCollisions = 5;
        elementCount = 0;
        map = new utility::Pair<K, V>*[mapSize];
        for(int i = 0; i < mapSize; i++)
        {
            map[i] = nullptr;
        }
    }
    
    template <typename K, typename V>
    HashMap<K, V>::~HashMap()
    {
        for(int i = 0; i < mapSize; i++)
        {
            if(map[i] != nullptr)
            {
                delete map[i];
            }
        }
        delete [] map;
    }
    
    template <typename K, typename V>
    bool HashMap<K, V>::contains(K key)
    {
        int firstLocation = hashK(key) % mapSize;
        int location = firstLocation;
        while(map[location] != nullptr)
        {
            if(map[location]->key == key)
            {
                return true;
            }
            location = location + 1 % mapSize;
            if(location == firstLocation)
            {
                break;
            }
        }
        
        return false;
    }
    
    template <typename K, typename V>
    void HashMap<K, V>::doubleSize()
    {
        utility::Pair<K, V>** oldMap = map;
        int oldMapSize = mapSize;
        mapSize *= 2;
        map = new utility::Pair<K, V>*[mapSize];
        for(int i = 0; i < mapSize; i++)
        {
            map[i] = nullptr;
        }
        for(int i = 0; i < oldMapSize; i++)
        {
            if(oldMap[i] != nullptr)
            {
                put(oldMap[i]->key, oldMap[i]->value);
                delete oldMap[i];
                oldMap[i] = nullptr;
            }
        }
        
        delete [] oldMap;
    }
    
    template <typename K, typename V>
    V HashMap<K, V>::get(K key)
    {
        int firstLocation = hashK(key) % mapSize;
        int location = firstLocation;
        while(map[location] != nullptr)
        {
            if(map[location]->key == key)
            {
                return map[location]->value;
            }
            location++;
            if(location == firstLocation)
            {
                break;
            }
        }
        
        std::cerr << "Key not in dictionary: " << key << std::endl;
        exit(-1);
    }
    
    template <typename K, typename V>
    int HashMap<K, V>::size()
    {
        return elementCount;
    }
    
    template <typename K, typename V>
    void HashMap<K, V>::put(K key, V value)
    {
        int location = hashK(key) % mapSize;
        int collisions = 0;
        while(true)
        {
            if(map[location] == nullptr)
            {
                map[location] = new utility::Pair<K, V>;
                map[location]->key = key;
                map[location]->value = value;
                elementCount++;
                return;
            }
            else if(map[location]->key == key)
            {
                map[location]->value = value;
                return;
            }
            location = location + 1 % mapSize;
            collisions++;
            if(collisions > maxCollisions)
            {
                doubleSize();
                put(key, value);
                return;
            }
        }
    }
    
    template <typename K, typename V>
    ArrayList<K> HashMap<K, V>::keyList()
    {
        ArrayList<K> output;
        for(int i = 0; i < mapSize; i++)
        {
            if(map[i] != nullptr)
            {
                output.add(map[i]->key);
            }
        }
        return output;
    }
}

#endif
