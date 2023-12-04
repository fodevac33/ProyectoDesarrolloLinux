<script lang="ts">
    import LeafletMap from '$lib/LeafletMap.svelte';
    import type { PageData } from './$types';
    import type { Data } from '@prisma/client';
    import { updateSensorData } from '$lib/util';
    import { browser } from '$app/environment';
    import { onMount } from 'svelte';

    export let data: PageData;

    let { sensorData } = data; 

    const update = async () => {
        sensorData = await updateSensorData();
    }	

    if (browser) {
        onMount(() => {
            const interval = setInterval(update, 1000); // Set up polling

            return () => {
                clearInterval(interval); // Cleanup on component destruction
            };
        });
    }
</script>

<main>
    <LeafletMap bind:sensorData={sensorData} />
</main>
