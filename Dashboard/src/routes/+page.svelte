<script lang="ts">
    import LeafletMap from '$lib/LeafletMap.svelte';
    import type { PageData } from './$types';
    import type { Data } from '@prisma/client';


    export let data: PageData;
</script>

<main>
    <LeafletMap />
</main>
