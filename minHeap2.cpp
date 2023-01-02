void minHeapify(int i)
    {
        int l = leftChild(i);
        int r = rightChild(i);
        int smallest = i;

        if (l < arr.size() && arr[l].arrivalTime < arr->at(smallest).arrivalTime)
        {
            smallest = l;
        }
        else
        {
            smallest = i;
        }

        if (right < arr->size() && arr->at(right).arrivalTime < arr->at(smallest).arrivalTime)
        {
            smallest = r;
        }

        if (smallest != parent)
        {
            swap(arr->at(smallest), arr->at(i));
            minHeapify(smallest);
        }
    }