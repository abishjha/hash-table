template <typename KEY, typename VALUE>
class Entry
{
     template<typename K, typename V> friend class HashTable;

private:
     KEY key;
     VALUE value;
     Entry * next_entry;

public:
     /*** Constructors ***/
     Entry(void) : key(KEY()), value(VALUE()), next_entry(NULL) {}
     Entry(KEY key, VALUE value)
     {
          this->key = key;
          this->value = value;
          this->next_entry = NULL;
     }
     Entry(KEY key, VALUE value, Entry * next) : key(key), value(value), next_entry(next) {}

     //accessors
     KEY get_key() { return key; }
     VALUE get_value() { return value; }
     Entry * get_next_entry() { return next_entry; }

     //mutators
     void set_key(KEY key) { this->key = key; }
     void set_value(VALUE value) { this->value = value; }
     void set_next_entry(Entry * entry) { this->next_entry = entry; }
};