<script lang="ts">
  import "../app.pcss";
  import { AppShell, AppBar } from '@skeletonlabs/skeleton';
  import SideBar from "$lib/SideBar.svelte";
  import type { LayoutData } from "./$types";
  import { browser } from "$app/environment";
  import { onMount } from "svelte";
  import { updateSensorData } from "$lib/util";

  export let data: LayoutData;


  let { sensorData } = data; 
  $: console.log(sensorData);

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


<AppShell>
	<svelte:fragment slot="header">
		<AppBar class="h1 font-bold shadow-lg">Dashboard Sistema Asistido</AppBar>
	</svelte:fragment>
	<svelte:fragment slot="sidebarLeft">
	<SideBar  bind:sensorData={sensorData} />
	</svelte:fragment>
	<slot />
</AppShell>
