<script lang="ts">
  import "../app.pcss";
  import { AppShell, AppBar } from '@skeletonlabs/skeleton';
  import SideBar from "$lib/SideBar.svelte";
  import type { LayoutData } from "./$types";
  import { browser } from "$app/environment";
  import { onMount } from "svelte";
  import type { SvelteComponent } from "svelte";

  export let data: LayoutData;

  let sideBarComp: SvelteComponent;

  let { sensorData } = data; 
  $: console.log(sensorData);

  const updateSensorData = async () => {
    try {
      const response = await fetch('/api/latest'); // replace with your actual API endpoint
      if (response.ok) {
        const newData = await response.json();
        sensorData = {...newData}; // Update sensorData with the latest data
		sideBarComp.$set(sensorData); //
      } else {
        throw new Error('Failed to fetch sensor data');
      }
    } catch (error) {
      console.error('Error fetching sensor data:', error);
    }
  }

  if (browser) {
    onMount(() => {
      const interval = setInterval(updateSensorData, 2000); // Set up polling

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
	<SideBar {...sensorData} bind:this={sideBarComp}/>
	</svelte:fragment>
	<slot />
</AppShell>
