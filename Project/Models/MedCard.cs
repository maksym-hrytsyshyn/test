using System.Collections.Concurrent;

namespace Project.Controllers;


public class MedCard<TKey, TValue>
{
    private readonly ConcurrentDictionary<TKey, TValue> _records = new();
    
    private class Node
    {
        public TKey Key { get; set; }
        public TValue Value { get; set; }
        public Node Next { get; set; }

        public Node(TKey key, TValue value)
        {
            Key = key;
            Value = value;
            Next = null;
        }
    }

    private const int Size = 1000000;
    private readonly List<Node> _table;

    public MedCard()
    {
        _table = new List<Node>(Size);
        for (int i = 0; i < Size; i++)
        {
            _table.Add(null!);
        }
    }

    private static int Hash(TKey key)
    {
        int hash = 0;
        foreach (char c in key.ToString()!)
        {
            hash = (hash * 10 + c) % Size;
        }
        return hash;
    }

    public void Insert(TKey key, TValue value)
    {
        int index = Hash(key);
        Node newNode = new Node(key, value);
        if (_table[index] != null)
        {
            Node current = _table[index];
            while (current.Next != null)
            {
                current = current.Next;
            }
            current.Next = newNode;
        }
        else
        {
            _table[index] = newNode;
        }
    }


    public bool Find(TKey key, out TValue value)
    {
        int index = Hash(key);
        Node current = _table[index];
        while (current != null)
        {
            if (current.Key.Equals(key))
            {
                value = current.Value;
                return true;
            }
            current = current.Next;
        }
        value = default!;
        return false;
    }

    public void Update(TKey key, TValue value)
    {
        int index = Hash(key);
        Node current = _table[index];
        while (current != null)
        {
            if (current.Key.Equals(key))
            {
                current.Value = value;
                return;
            }
            current = current.Next;
        }
        throw new KeyNotFoundException("Key not found in hash table");
    }


    public void Remove(TKey key)
    {
        int index = Hash(key);
        Node current = _table[index];
        Node prev = null!;
        while (current != null)
        {
            if (current.Key.Equals(key))
            {
                if (prev != null)
                {
                    prev.Next = current.Next;
                }
                else
                {
                    _table[index] = current.Next;
                }
                return;
            }
            prev = current;
            current = current.Next;
        }
    }

    public TKey MakeMedCard(TValue record, out TKey key)
    {
        // Generate a new key (for simplicity, using Guid)
        key = (TKey)(object)Guid.NewGuid().ToString();

        _records[key] = record;
        return key;
    }

    public List<TKey> GetAllKeys()
    {
        List<TKey> keys = new List<TKey>();
        for (int i = 0; i < Size; i++)
        {
            Node current = _table[i];
            while (current != null)
            {
                keys.Add(current.Key);
                current = current.Next;
            }
        }
        return keys;
    }
}