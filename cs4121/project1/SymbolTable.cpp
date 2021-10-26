#include "SymbolTable.hpp"

namespace project1
{
    /**
     * Default constructor for the symbol table.
     *
     * There's not really any setup that is done here.
     */
    SymbolTable::SymbolTable()
    {
        
    }
    
    /**
     * Deconstructor for the symbol table.
     *
     * Deallocates space for all pairs, strings, and ArrayLists.
     */
    SymbolTable::~SymbolTable()
    {
        // Iterate over every Pair in the table.
        for(int i = 0; i < table.size(); i++)
        {
            // Delete the string label.
            delete table.get(i)->value;
            // Delete the ArrayList.
            delete table.get(i)->key;
            // Delete the Pair.
            delete table.get(i);
        }
        // Delete every string pointer in the columnNames array.
        for(int i = 0; i < columnNames.size(); i++)
        {
            // Delete the string at the index.
            delete columnNames.get(i);
        }
    }
    
    /**
     * Check if the given name is in the symbol table.
     * Returns the index if it is, -1 otherwise.
     *
     * @param name pointer to string used as name to search for.
     * @return Index of the name, or -1 if none.
     */
    int SymbolTable::queryIndex(std::string* name)
    {
        // Get the size of the table.
        int size = table.size();
        
        // Search for the value.
        for(int i = 0; i < size; i++)
        {
            // Use string comparison to check equality.
            if(name->compare(*table.get(i)->key) == 0)
            {
                // Return the index.
                return i;
            }
        }
        // Return -1, since the value was not found.
        return -1;
    }
    
    /**
     * Gets the index of the name, placing it if it doesn't exist.
     *
     * @param name The name to search for in the table.
     * @return Index of the name.
     */
    int SymbolTable::index(std::string* name)
    {
        // Get the size of the table.
        int size = table.size();

        // Iterate over the table to search for the name.
        for(int i = 0; i < size; i++)
        {
            // Compare each string using the string comparing function.
            if(name->compare(*table.get(i)->key) == 0)
            {
                // Return the index of the found name.
                return i;
            }
        }
        // Create a new Pair to store the name.
        dasker::collections::utility::Pair<std::string*, dasker::collections::ArrayList<void*>*>* pair;
        pair = new dasker::collections::utility::Pair<std::string*, dasker::collections::ArrayList<void*>*>;

        // Set the key to the given name.
        pair->key = name;

        // Set the value to a new ArrayList to store any fields.
        pair->value = new dasker::collections::ArrayList<void*>;

        // Initialize each field with a nullptr.
        for(int i = 0; i < columnNames.size(); i++)
        {
             pair->value->add(nullptr);
        }

        // Return the index the pair was added at.
        return table.add(pair);
    }
    
    /**
     * Check whether the given field exists in the table.
     *
     * @param field The name of the field to check.
     * @return The index of the field if it exists, otherwise -1;
     */
    int SymbolTable::fieldExists(std::string* field)
    {
        // Get the size of the columnNames list.
        int size = columnNames.size();

        // Iterate over the list.
        for(int i = 0; i < size; i++)
        {
            // Compare the field given to each field in the list.
            if(columnNames.get(i)->compare(*field) == 0)
            {
                // Return the found index of the field.
                return i;
            }
        }
        // The field wasn't found, so return -1;
        return -1;
    }
    
    /**
     * Initializes a new field in the symbol table.
     *
     * If any names are already in the table, their values are initialized to nullptr.
     *
     * @param field The name of the new field to initialize.
     * @return The index of where the field was placed.
     */
    int SymbolTable::initField(std::string* field)
    {
        // Check if the field already exists.
        if(fieldExists(field) > -1)
        {
            // Print an error and exit the program.
            std::cerr << "Field exists, cannot init!\n";
            exit(-1);
        }
        
        // Add the field and save the index.
        int index = columnNames.add(field);
        
        // Initialize the field in every name saved in the table.
        int size = table.size();
        for(int i = 0; i < size; i++)
        {
            table.get(i)->value->add(nullptr);
        }
        
        // Return the index of the field.
        return index;
    }
    
    /**
     * Macro allowing initialization of a field using a string constant.
     *
     * @param field Name of the field to initialize.
     * @return The index where the field was initialized.
     */
    int SymbolTable::initField(const char* field)
    {
        // Convert the field name to a cpp string.
        // We use new because it's saved in the table, and will be disposed of later.
        std::string* value = new std::string(field);

        // Return the index after initialization.
        return initField(value);
    }
    
    /**
     * Sets the value of a field at the given index.
     *
     * Will print and error and ixit if the field or index doesn't exist.
     * Because we're just storing the field as void*, we don't worry about
     * overwriting any values - users are responsible for freeing fields.
     *
     * @param index The index of the symbol in the table to update the field for.
     * @param fieldName The name of the field to update the value for.
     * @param value The value to store.
     */
    void SymbolTable::putFieldByIndex(int index, std::string* fieldName, void* value)
    {
        // Verify the index exists.
        if(index < 0 || index >= table.size())
        {
            std::cerr << "Cannot put field at index that doesn't exist!\n";
            exit(-1);
        }
        // Verify the field exists.
        int field = fieldExists(fieldName);
        if(field < 0)
        {
            std::cerr << "Cannot put at field that doesn't exist!\n";
            exit(-1);
        }
        // Set the value of the field.
        table.get(index)->value->set(field, value);
    }
    
    /**
     * Macro allowing us to put the field by index using a constant for the field name.
     *
     * @param index Index of the name to update the field for.
     * @param fieldName Name of the field to update the value of.
     * @param value Value to set the field to.
     */
    void SymbolTable::putFieldByIndex(int index, const char* fieldName, void* value)
    {
        // Convert the field to a string and use the string function.
        std::string name(fieldName);
        return putFieldByIndex(index, &name, value);
    }
    
    /**
     * Updates the given symbol's value of the given field.
     *
     * Will error if the name or field doesn't exit.
     *
     * @param name Name of the symbol whose field we're updating.
     * @param fieldName Name of the field we are updating.
     * @param value Value to set the field to.
     */
    void SymbolTable::putField(std::string* name, std::string* fieldName, void* value)
    {
        // Get the index of the name given.
        int index = queryIndex(name);
        // Print an error and exit if it doesn't exist.
        if(index == -1)
        {
            std::cerr << "Cannot put name that doesn't exist!\n";
            exit(-1);
        }
        // Use our function to put the field by index.
        putFieldByIndex(index, fieldName, value);
    }
    
    /**
     * Get the value of the field at the given index in the symbol table.
     *
     * Will error if the index or field doesn't exist.
     *
     * @param index Index to get the field value from.
     * @param fieldName Name of the field to get the value of.
     * @return Value of the field at the given index.
     */
    void* SymbolTable::getFieldByIndex(int index, std::string* fieldName)
    {
        // Verify the index is within bounds.
        if(index < 0 || index >= table.size())
        {
            std::cerr << "Cannot get field from index that doesn't exist!\n";
            exit(-1);
        }
        // Verify the field exists in the table.
        int fieldIndex = fieldExists(fieldName);
        if(fieldIndex < 0)
        {
            std::cerr << "Cannot get field from field that doesn't exist\n";
            exit(-1);
        }
        
        // Return the value currently stored in the field.
        return table.get(index)->value->get(fieldIndex);
    }
    
    /**
     * Macro for getting the value of a symbol at the given index
     * using a string constant for the fieldName.
     *
     * @param index Index of the symbol to get the field value of.
     * @param fieldName Name of the field to get the value of.
     * @return The value of the given field for the symbol.
     */
    void* SymbolTable::getFieldByIndex(int index, const char* fieldName)
    {
        // Convert the fieldName to a cpp string.
        std::string name(fieldName);
        // Return the value at the index.
        return getFieldByIndex(index, &name);
    }
    
    /**
     * Gets the value of the given field for the given symbol.
     *
     * Will error if the field or symbol do not exist.
     *
     * @param name Name of the symbol to get the field value for.
     * @param fieldName Name of the field to get the value for.
     * @return The value of the field for the symbol.
     */
    void* SymbolTable::getField(std::string* name, std::string* fieldName)
    {
        // Get the index of the symbol.
        int index = queryIndex(name);

        // Error if the symbol doesn't exist.
        if(index < 0)
        {
            std::cerr << "Cannot get field from name that doesn't exist!'\n";
            exit(-1);
        }

        // Return the value at the field.
        return getFieldByIndex(index, fieldName);
    }
    
    /**
     * Gets the name of the symbol at the given index.
     *
     * @return The name of the symbol.
     */
    std::string* SymbolTable::nameAtIndex(int index)
    {
        // Error if the index doesn't exist.
        if(index < 0 || index >= table.size())
        {
            std::cerr << "Cannot get name at invalid index!\n";
            exit(-1);
        }

        // Return the symbol name.
        return table.get(index)->key;
    }
    
    /**
     * Gets a list of all values in a given field.
     * Not guaranteed to be in any particular order, and not
     * updated when the symbol table is updated.
     * Should be used mostly for cleanup.
     *
     * @param fieldName Name of the field to get all values for.
     * @return ArrayList containing all values in the field.
     */
    dasker::collections::ArrayList<void*> SymbolTable::getFieldList(std::string* fieldName)
    {
        // Error if the field doesn't exist.
        int index = fieldExists(fieldName);
        if(index < 0)
        {
            std::cerr << "Cannot get list of invalid field!\n";
            exit(-1);
        }

        // Create the array.
        dasker::collections::ArrayList<void*> output;

        // Add all values to the array.
        for(int i = 0; i < table.size(); i++)
        {
            output.add(table.get(i)->value->get(index));
        }

        // Return the array as the output.
        return output;
    }
    
    /**
     * Macro for getting the fieldList using a string constant.
     *
     * @param fieldName Name of the field to get the list for.
     * @return ArrayList containing all values in the field.
     */
    dasker::collections::ArrayList<void*> SymbolTable::getFieldList(const char* fieldName)
    {
        // Convert the fieldName to a cpp string.
        std::string name(fieldName);

        // Get and return the fieldList.
        return getFieldList(&name);
    }
}
