// Program: SequenceMap.h
// Author : Kazuki Sona
// Date   : March 8th, 2018

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <vector>

using namespace std;

class SequenceMap {

public:
    // constructor default
    SequenceMap(): recognition_sequence_{""}, enzyme_acronyms_{""} {}

    SequenceMap(const string &a_rec_seq, const string &an_enz_acro):
        recognition_sequence_{a_rec_seq}, enzyme_acronyms_{an_enz_acro} {}

    // destructor
    ~SequenceMap() {}

    // copy constructor
    SequenceMap(const SequenceMap &rhs): recognition_sequence_{rhs.recognition_sequence_}, 
        enzyme_acronyms_{rhs.enzyme_acronyms_} { }

    // copy assignment
    SequenceMap & operator=(const SequenceMap &rhs) {
        if (this != &rhs) {
            recognition_sequence_ = rhs.recognition_sequence_;
            enzyme_acronyms_ = rhs.enzyme_acronyms_;
        }
        return *this;
    }

    // move constructor
    SequenceMap(SequenceMap &&rhs): recognition_sequence_{rhs.recognition_sequence_},
        enzyme_acronyms_{rhs.enzyme_acronyms_} {
            rhs.recognition_sequence_ = "";
            rhs.enzyme_acronyms_.clear();
    }

    // move assignment
    SequenceMap operator =(SequenceMap &&rhs) {
        swap(recognition_sequence_, rhs.recognition_sequence_);
        swap(enzyme_acronyms_, rhs.enzyme_acronyms_);

        return *this;
    }

    // operator ==
    bool operator ==(const SequenceMap &rhs) const {
        return recognition_sequence_ == rhs.recognition_sequence_;
    }

    // operator <
    bool operator <(const SequenceMap &rhs) const {
        return recognition_sequence_ < rhs.recognition_sequence_;
    }

    // @&other_sequence: SequenceMap object to be merged into this object
    // pre-condition: recognition sequence is the same to one of other_sequence
    // post-condition: enzyme_acronyms_ is merged with other_sequence's enzyme_acronyms_
    void Merge(const SequenceMap &other_sequence) {
        enzyme_acronyms_.insert(enzyme_acronyms_.end(), other_sequence.enzyme_acronyms_.begin(), 
                                other_sequence.enzyme_acronyms_.end());
    }

    // opeartor <<
    friend ostream& operator <<(ostream &os, SequenceMap &smap);

private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;
};

ostream& operator <<(ostream &os, SequenceMap &smap) {
    for (vector<string>::iterator it = smap.enzyme_acronyms_.begin(); it != smap.enzyme_acronyms_.end(); ++it) {
        os << *it << " ";
    }

    return os;
}

#endif