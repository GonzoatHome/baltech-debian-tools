#include "brp_lib/ioiter.h"
#include "brp_lib/usb_hid_protocol.h"
#include "brp_lib/errorcodes.h"
#include <stdlib.h>


// Composite iterator structure
// Inherits from brp_ioiter_t by having it as the first member
typedef struct brp_ioiter_composite_t
{
	struct brp_ioiter_t base;           // FIRST MEMBER - base iterator
	brp_ioiter usb_hid_iter;            // USB HID-specific iterator
} * brp_ioiter_composite;


// Forward declaration of USB HID iterator creation function
// (will be implemented in usb_hid_protocol.c)
extern brp_ioiter brp_ioiter_create_usb_hid(void);


// Composite iterator next function
static brp_errcode composite_ioiter_next(brp_ioiter iter, brp_protocol* protocol)
{
	brp_ioiter_composite comp_iter = (brp_ioiter_composite) iter;

	if (comp_iter->usb_hid_iter == NULL)
	{
		// No more protocols to iterate
		*protocol = NULL;
		return BRP_OK;
	}

	// Try to get next device from USB HID iterator
	brp_errcode errcode = brp_ioiter_next(comp_iter->usb_hid_iter, protocol);

	// If error, fail immediately (per requirement)
	if (errcode != BRP_OK)
		return errcode;

	// If USB HID iterator is exhausted, clean it up and mark as done
	if (*protocol == NULL)
	{
		brp_ioiter_destroy(&comp_iter->usb_hid_iter);
		comp_iter->usb_hid_iter = NULL;
		// In the future, we would continue with the next protocol type here
		// For now, we're done
	}

	return BRP_OK;
}


// Composite iterator destroy function
static void composite_ioiter_destroy(brp_ioiter iter)
{
	brp_ioiter_composite comp_iter = (brp_ioiter_composite) iter;

	// Destroy USB HID iterator if still active
	if (comp_iter->usb_hid_iter != NULL)
		brp_ioiter_destroy(&comp_iter->usb_hid_iter);
}


brp_ioiter brp_ioiter_create(void)
{
	// Allocate composite iterator structure
	brp_ioiter_composite iter = (brp_ioiter_composite) malloc(sizeof(struct brp_ioiter_composite_t));
	if (iter == NULL)
		return NULL;

	// Set up callbacks
	iter->base.next_fn = composite_ioiter_next;
	iter->base.destroy_fn = composite_ioiter_destroy;

	// Create USB HID iterator
	iter->usb_hid_iter = brp_ioiter_create_usb_hid();
	if (iter->usb_hid_iter == NULL)
	{
		free(iter);
		return NULL;
	}

	return (brp_ioiter) iter;
}


brp_errcode brp_ioiter_next(brp_ioiter iter, brp_protocol* protocol)
{
	if (iter == NULL || protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	// Call the iterator's next function callback
	return iter->next_fn(iter, protocol);
}


void brp_ioiter_destroy(brp_ioiter* iter)
{
	if (iter == NULL || *iter == NULL)
		return;

	// Call the iterator's destroy function callback
	if ((*iter)->destroy_fn != NULL)
		(*iter)->destroy_fn(*iter);

	// Free iterator structure
	free(*iter);
	*iter = NULL;
}
