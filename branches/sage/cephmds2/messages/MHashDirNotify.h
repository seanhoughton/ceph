// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2004-2006 Sage Weil <sage@newdream.net>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software 
 * Foundation.  See file COPYING.
 * 
 */


#ifndef __MHASHDIRNOTIFY_H
#define __MHASHDIRNOTIFY_H

#include "msg/Message.h"

class MHashDirNotify : public Message {
  inodeno_t ino;
  int from;

 public:
  inodeno_t get_ino() { return ino; }
  int get_from() { return from; }

  MHashDirNotify() {}
  MHashDirNotify(inodeno_t ino, int from) :
    Message(MSG_MDS_HASHDIRNOTIFY) {
    this->ino = ino;
    this->from = from;
  }  
  virtual char *get_type_name() { return "HN"; }
  
  virtual void decode_payload() {
    int off = 0;
    payload.copy(off, sizeof(ino), (char*)&ino);
    off += sizeof(ino);
    payload.copy(off, sizeof(from), (char*)&from);
    off += sizeof(from);
  }
  virtual void encode_payload() {
    payload.append((char*)&ino, sizeof(ino));
    payload.append((char*)&from, sizeof(from));
  }

};

#endif
