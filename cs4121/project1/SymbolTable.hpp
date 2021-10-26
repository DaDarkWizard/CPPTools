
#include "HashMap.hpp"
#include "ArrayList.hpp"

#ifndef PROJECT1_SYMBOLTABLE_H
#define PROJECT1_SYMBOLTABLE_H

namespace project1
{
    /*
     * cpp implementation of the SymbolTable.
     */
    class SymbolTable
    {
        private:
            dasker::collections::ArrayList<dasker::collections::utility::Pair<
                                                std::string*,
                                                dasker::collections::ArrayList<void*>*
                                                >*> table;
            dasker::collections::ArrayList<std::string*> columnNames;
        public:
            SymbolTable();
            ~SymbolTable();
            int queryIndex(std::string* name);
            int index(std::string* name);
            int fieldExists(std::string* field);
            int initField(std::string* field);
            int initField(const char* field);
            void putFieldByIndex(int index, std::string* fieldName, void* value);
            void putFieldByIndex(int index, const char* fieldName, void* value);
            void putField(std::string* name, std::string* fieldName, void* value);
            void* getFieldByIndex(int index, std::string* fieldName);
            void* getFieldByIndex(int index, const char* fieldName);
            void* getField(std::string* name, std::string* fieldName);
            std::string* nameAtIndex(int index);
            dasker::collections::ArrayList<void*> getFieldList(std::string* fieldName);
            dasker::collections::ArrayList<void*> getFieldList(const char* fieldName);
    };
}

#endif
