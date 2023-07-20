typedef struct {
    int item_layout_sequence[6];
    int device_use_sequence[6];
    int item_take_sequence[6];
}device_item_sequence;

device_item_sequence sequence1{{1, 1, 1, 0, 0, 0
},
{5,0,1,2,3,4,},{0,1,2,3,4,5,}};


device_item_sequence sequence2{{1, 0, 1, 1, 0, 0
},
{4,5,0,1,2,3,},{1,0,2,3,4,5,}};


device_item_sequence sequence3{{0, 1, 1, 0, 0, 1
},
{2,3,0,4,5,1,},{3,4,2,0,1,5,}};


device_item_sequence sequence4{{1, 1, 0, 0, 1, 0
},
{4,2,3,0,5,1,},{5,2,3,1,0,4,}};


device_item_sequence sequence5{{1, 1, 0, 0, 0, 1
},
{0,1,2,3,4,5,},{0,1,2,3,4,5,}};


device_item_sequence sequence6{{1, 0, 0, 0, 1, 1
},
{4,0,1,5,2,3,},{1,4,5,0,2,3,}};


device_item_sequence sequence7{{1, 0, 1, 0, 1, 0
},
{3,4,1,5,0,2,},{1,3,4,0,2,5,}};


device_item_sequence sequence8{{1, 0, 0, 1, 0, 1
},
{4,5,2,3,0,1,},{4,5,1,2,0,3,}};


device_item_sequence sequence9{{1, 0, 0, 1, 1, 0
},
{3,4,0,1,5,2,},{1,2,3,4,0,5,}};


device_item_sequence sequence10{{0, 1, 0, 0, 1, 1
},
{2,3,4,5,0,1,},{2,3,0,1,4,5,}};


device_item_sequence sequence11{{1, 0, 1, 0, 0, 1
},
{0,1,3,2,4,5,},{2,0,3,1,4,5,}};


device_item_sequence sequence12{{1, 1, 0, 1, 0, 0
},
{0,5,1,3,2,4,},{3,0,1,4,2,5,}};


device_item_sequence sequence13{{0, 0, 1, 0, 1, 1
},
{2,3,4,5,0,1,},{0,1,3,2,4,5,}};


device_item_sequence sequence14{{0, 1, 1, 0, 1, 0
},
{4,3,5,1,0,2,},{3,0,1,4,2,5,}};


device_item_sequence sequence15{{0, 1, 0, 1, 1, 0
},
{3,4,5,0,1,2,},{0,2,1,3,4,5,}};


device_item_sequence sequence16{{0, 0, 1, 1, 1, 0
},
{3,4,5,0,1,2,},{0,1,2,3,4,5,}};


device_item_sequence sequence17{{0, 1, 0, 1, 0, 1
},
{3,4,0,5,1,2,},{0,2,5,1,3,4,}};


device_item_sequence sequence18{{0, 0, 0, 1, 1, 1
},
{2,3,4,5,0,1,},{0,1,2,3,4,5,}};


device_item_sequence sequence19{{0, 0, 1, 1, 0, 1
},
{3,4,5,1,0,2,},{0,1,2,5,3,4,}};


device_item_sequence sequence20{{0, 1, 1, 1, 0, 0
},
{4,5,0,1,2,3,},{0,1,2,3,4,5,}};

device_item_sequence * psequences_array[20] = {
&sequence1,
&sequence2,
&sequence3,
&sequence4,
&sequence5,
&sequence6,
&sequence7,
&sequence8,
&sequence9,
&sequence10,
&sequence11,
&sequence12,
&sequence13,
&sequence14,
&sequence15,
&sequence16,
&sequence17,
&sequence18,
&sequence19,
&sequence20};