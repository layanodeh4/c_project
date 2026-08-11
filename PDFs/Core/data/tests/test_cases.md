# LexiCore Test Cases

| Test ID | Test Description | Input / Action | Expected Result | Status |
| :--- | :--- | :--- | :--- | :--- |
| TC01 | Load valid dictionary | Menu Option 1 (`data/dictionary.txt`) | All valid entries loaded successfully | Pass |
| TC02 | Load missing file | Menu Option 1 (`data/non_existent.txt`) | Error message, program continues | Pass |
| TC03 | Load malformed file | Menu Option 1 (`data/test_dictionary.txt`) | Invalid lines ignored with warning | Pass |
| TC04 | Search existing word | Search `pointer` | Displays part of speech, definition, example | Pass |
| TC05 | Search missing word | Search `unknownword` | Displays not-found message | Pass |
| TC06 | Search case-insensitive | Search `ALGORITHM` | Finds `algorithm` successfully | Pass |
| TC07 | Add new word | Add `protocol` | Word added to hash table | Pass |
| TC08 | Reject duplicate word | Add existing `pointer` | Addition rejected | Pass |
| TC09 | Delete word | Delete `compile` | Entry removed, memory freed | Pass |
| TC10 | Delete non-existing word | Delete `xyz` | Displays not-found message | Pass |
| TC11 | Display Statistics | Menu Option 5 | Shows load factor, chain length, counts | Pass |
| TC12 | Save to file | Save to `data/saved.txt` | File created with correct pipe format | Pass |
| TC13 | Invalid menu input | Enter `abc` on menu | Prompt shows error and re-asks choice | Pass |
| TC14 | Memory Leak Check | Run via `valgrind` | Zero dynamic leaks reported | Pass |
| TC15 | Exit application | Menu Option 0 | Dynamic memory freed, clean exit | Pass |