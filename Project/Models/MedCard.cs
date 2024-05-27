namespace Project.Models;

// public class Template
// {
//     
// }
public class MedCard<Key, Value> where Key : IComparable<Key>, IEquatable<Key>
{
    private class Node(Key key, Value value)
    {
        public Key Key { get; set; } = key;
        public Value Value { get; set; } = value;
        public Node Next { get; set; } = null!;
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

    private static int Hash(Key key)
    {
        int hash = 0;
        foreach (char c in key.ToString()!)
        {
            hash = (hash * 10 + c) % Size;
        }
        return hash;
    }

    public void Insert(Key key, Value value)
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

        _table[index] = newNode;

    }

    public bool Find(Key key, out Value value)
    {
        int index = Hash(key);
        Node current = _table[index];
        while (current != null)
        {
            if (!current.Key.Equals(key))
            {
                current = current.Next;
            }
            
            value = current.Value;
            return true;

        }
        value = default!;
        return false;
    }

    public void Update(Key key, Value value)
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
        Console.WriteLine("Key not found in hash table");
    }

    public void Remove(Key key)
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

    public string MakeMedCard(MedicalRecord patient, out string patientId)
    {
        patientId = DataGenerator.GenerateRandomId();
        Insert((Key)(object)patientId, (Value)(object)patient);
        return patientId;
    }

    public List<Key> GetAllKeys()
    {
        List<Key> keys = new List<Key>();
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