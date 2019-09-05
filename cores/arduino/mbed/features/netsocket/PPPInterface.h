/*
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PPP_INTERFACE_H
#define PPP_INTERFACE_H

#include "nsapi.h"
#include "OnboardNetworkStack.h"
#include "NetworkInterface.h"
#include "PPP.h"


/** PPPInterface class
 *  Implementation of the NetworkInterface for an PPP-service
 *
 * This class provides the necessary glue logic to create a NetworkInterface
 * based on an PPP and an OnboardNetworkStack.
 *
 */
class PPPInterface : public virtual NetworkInterface {
public:
    /** Create an PPP-based network interface.
     *
     * The default arguments obtain the default PPP, which will be target-
     * dependent (and the target may have some JSON option to choose which
     * is the default, if there are multiple). The default stack is configured
     * by JSON option nsapi.default-stack.
     *
     * Due to inability to return errors from the constructor, no real
     * work is done until the first call to connect().
     *
     * @param ppp  Reference to PPP to use
     * @param stack Reference to onboard-network stack to use
     */
    PPPInterface(PPP &ppp = PPP::get_default_instance(),
                 OnboardNetworkStack &stack = OnboardNetworkStack::get_default_instance());
    virtual ~PPPInterface();

    /** Set a static IP address
     *
     *  Configures this network interface to use a static IP address.
     *  Implicitly disables DHCP, which can be enabled in set_dhcp.
     *  Requires that the network is disconnected.
     *
     *  @param ip_address  Null-terminated representation of the local IP address
     *  @param netmask     Null-terminated representation of the local network mask
     *  @param gateway     Null-terminated representation of the local gateway
     *  @return            0 on success, negative error code on failure
     */
    virtual nsapi_error_t set_network(const char *ip_address, const char *netmask, const char *gateway);

    /** Start the interface
     *  @return             0 on success, negative on failure
     */
    virtual nsapi_error_t connect();

    /** Stop the interface
     *  @return             0 on success, negative on failure
     */
    virtual nsapi_error_t disconnect();

    /** Get the local IP address
     *
     *  @return         Null-terminated representation of the local IP address
     *                  or null if no IP address has been received
     */
    virtual const char *get_ip_address();

    /** Get the local network mask
     *
     *  @return         Null-terminated representation of the local network mask
     *                  or null if no network mask has been received
     */
    virtual const char *get_netmask();

    /** Get the local gateways
     *
     *  @return         Null-terminated representation of the local gateway
     *                  or null if no network mask has been received
     */
    virtual const char *get_gateway();

    /** Get the network interface name
     *
     *  @return         Null-terminated representation of the network interface name
     *                  or null if  interface not exists
     */
    virtual char *get_interface_name(char *interface_name);

    /** Set the network interface as default one
      */
    virtual void set_as_default();

    /** Register callback for status reporting
     *
     *  @param status_cb The callback for status changes
     */
    virtual void attach(mbed::Callback<void(nsapi_event_t, intptr_t)> status_cb);

    /** Get the connection status
     *
     *  @return         The connection status according to nsapi_connection_status_t
     */
    virtual nsapi_connection_status_t get_connection_status() const;

    /** Set blocking status of connect() which by default should be blocking
     *
     *  @param blocking true if connect is blocking
     *  @return         0 on success, negative error code on failure
     */
    virtual nsapi_error_t set_blocking(bool blocking);

    /** Sets file stream used to communicate with modem
     *
     * @param stream Pointer to file handle
     */
    virtual void set_stream(mbed::FileHandle *stream);

    /** Sets IP protocol versions of IP stack
     *
     * @param ip_stack IP protocol version
     */
    virtual void set_ip_stack(nsapi_ip_stack_t ip_stack);

    /** Sets user name and password for PPP protocol
     *
     * @param uname    User name
     * @param password Password
     */
    virtual void set_credentials(const char *uname, const char *password);

    /** Provide access to the PPP
     *
     * This should be used with care - normally the network stack would
     * control the PPP, so manipulating the PPP while the stack
     * is also using it (ie after connect) will likely cause problems.
     *
     * @return          Reference to the PPP in use
     */
    PPP &getppp() const
    {
        return _ppp;
    }

    virtual PPPInterface *pppInterface()
    {
        return this;
    }

protected:
    /** Provide access to the underlying stack
     *
     *  @return The underlying network stack
     */
    virtual NetworkStack *get_stack();

    PPP &_ppp;
    OnboardNetworkStack &_stack;
    OnboardNetworkStack::Interface *_interface;
    bool _blocking;
    char _ip_address[NSAPI_IPv6_SIZE];
    char _netmask[NSAPI_IPv4_SIZE];
    char _gateway[NSAPI_IPv4_SIZE];
    mbed::Callback<void(nsapi_event_t, intptr_t)> _connection_status_cb;

    mbed::FileHandle *_stream;
    nsapi_ip_stack_t _ip_stack;
    const char *_uname;
    const char *_password;

};

#endif
