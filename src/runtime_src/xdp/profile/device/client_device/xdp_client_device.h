/**
 * Copyright (C) 2019-2022 Xilinx, Inc
 * Copyright (C) 2022-2023 Advanced Micro Devices, Inc. - All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may
 * not use this file except in compliance with the License. A copy of the
 * License is located at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */


#ifndef _XDP_PROIFLE_XDP_CLIENT_DEVICE_H
#define _XDP_PROIFLE_XDP_CLIENT_DEVICE_H

#include<vector>
#include "core/include/xrt.h"
#include "core/include/xrt/xrt_bo.h"
#include "xdp/profile/device/xdp_base_device.h"

namespace xdp {

class ClientDevice : public xdp::Device
{
  xclDeviceHandle mClientDevice;
  std::vector<xrt::bo> xrt_bos;

public:
  ClientDevice(void* ClientDeviceHandle);
  virtual ~ClientDevice();

  virtual std::string getDebugIPlayoutPath();
  virtual uint32_t getNumLiveProcesses();
  virtual int write(xclAddressSpace space, uint64_t offset, const void *hostBuf, size_t size);
  virtual int read(xclAddressSpace space, uint64_t offset, void *hostBuf, size_t size);
  virtual int unmgdRead(unsigned flags, void *buf, size_t count, uint64_t offset);

  virtual int readXrtIP(uint32_t id, uint32_t offset, uint32_t *data);
  virtual int initXrtIP(const char *name, uint64_t base, uint32_t range);

  virtual std::vector<char> getDebugIpLayout();

  virtual double getDeviceClock();
  virtual uint64_t getTraceTime();
  virtual int getTraceBufferInfo(uint32_t nSamples, uint32_t& traceSamples, uint32_t& traceBufSz);
  virtual int readTraceData(void* traceBuf, uint32_t traceBufSz, uint32_t numSamples, uint64_t ipBaseAddress, uint32_t& wordsPerSample);

  virtual size_t alloc(size_t sz, uint64_t memoryIndex);
  virtual void   free(size_t id);
  virtual void*  map(size_t id);
  virtual void   unmap(size_t id);
  virtual void   sync(size_t id, size_t sz, size_t offset, direction dir, bool async=false);
  virtual xclBufferExportHandle exportBuffer(size_t id);
  virtual uint64_t              getBufferDeviceAddr(size_t id);

  virtual void* getRawDevice() { return mClientDevice ; }

  virtual double getHostMaxBwRead();
  virtual double getHostMaxBwWrite();
  virtual double getKernelMaxBwRead();
  virtual double getKernelMaxBwWrite();

  virtual std::string getSubDevicePath(std::string& subdev, uint32_t index);

};
}

#endif 
