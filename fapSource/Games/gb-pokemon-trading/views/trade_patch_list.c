#include "../pokemon_app.h"
#include "trade_patch_list.h"

struct patch_list* plist_alloc(void) {
    struct patch_list* plist = NULL;

    plist = malloc(sizeof(struct patch_list));
    plist->index = 0;
    plist->next = NULL;
    return plist;
}

void plist_append(struct patch_list* plist, uint8_t index) {
    furi_assert(plist);

    for(;;) {
        if(plist->next == NULL) break;
        plist = plist->next;
    }
    plist->index = index;
    plist->next = plist_alloc();
}

void plist_free(struct patch_list* plist) {
    struct patch_list* plist_next = NULL;

    while(plist != NULL) {
        plist_next = plist->next;
        free(plist);
        plist = plist_next;
    }
}

/* Returns the index value at offset member of the list. If offset is beyond
 * the length of the allocated list, it will just return 0.
 */
uint8_t plist_index_get(struct patch_list* plist, int offset) {
    furi_assert(plist);
    int i;

    for(i = 0; i < offset; i++) {
        if(plist->next == NULL) break;
        plist = plist->next;
    }

    return plist->index;
}

void plist_create(struct patch_list** pplist, TradeBlock* trade_block) {
    furi_assert(trade_block);
    uint8_t* trade_party_flat = (uint8_t*)trade_block->party;
    int i;

    /* If plist is non-NULL that means its already been created. Tear it down
     * first.
     */
    if(*pplist != NULL) {
        plist_free(*pplist);
        *pplist = NULL;
    }

    *pplist = plist_alloc();
    /* NOTE: 264 magic number is the length of the party block, 44 * 6 */
    /* The first half of the patch list covers offsets 0x00 - 0xfb, which
     * is expressed as 0x01 - 0xfc. An 0xFF byte is added to signify the
     * end of the first part. The second half of the patch list covers
     * offsets 0xfc - 0x107. Which is expressed as 0x01 - 0xc. A 0xFF byte
     * is added to signify the end of the second part/
     */
    for(i = 0; i < 264; i++) {
        FURI_LOG_D(TAG, "%02X", trade_party_flat[i]);
        if(i == 0xFC) {
            FURI_LOG_D(TAG, "[plist] part 1 end");
            plist_append(*pplist, 0xFF);
        }

        if(trade_party_flat[i] == 0xFE) {
            FURI_LOG_D(
                TAG, "[plist] patching byte 0x%02X, adding 0x%02X to plist", i, (i % 0xfc) + 1);
            plist_append(*pplist, (i % 0xfc) + 1);
            trade_party_flat[i] = 0xFF;
        }
    }
    FURI_LOG_D(TAG, "[plist] part 2 end");
    plist_append(*pplist, 0xFF);
}
