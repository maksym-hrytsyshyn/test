using Project.Controllers;
using Project.Models;

namespace Project;

public class Startup
{
    public Startup(IConfiguration configuration)
    {
        Configuration = configuration;
    }

    public IConfiguration Configuration { get; }

    public void ConfigureServices(IServiceCollection services)
    {
        services.AddControllersWithViews();
        services.AddSingleton<MedCard<string, MedicalRecord>>();
    }

    public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
    {
        if (env.IsDevelopment())
        {
            app.UseDeveloperExceptionPage();
        }
        else
        {
            app.UseExceptionHandler("/Home/Error");
            app.UseHsts();
        }

        app.UseHttpsRedirection();
        app.UseStaticFiles();
        app.UseRouting();
        app.UseAuthorization();

        app.UseEndpoints(endpoints =>
        {
            endpoints.MapControllerRoute(
                name: "default",
                pattern: "{controller=Home}/{action=Index}/{id?}");
                
            endpoints.MapControllerRoute(
                name: "medicalrecord",
                pattern: "{controller=MedicalRecord}/{action=Index}/{id?}");
            
            endpoints.MapControllerRoute(
                name: "viewMedicalCards",
                pattern: "Home/Records",
                defaults: new { controller = "Home", action = "Records" });
            
            endpoints.MapControllerRoute(
                name: "doctors",
                pattern: "Doctors",
                defaults: new { controller = "Doctor", action = "Index" });
            
            endpoints.MapControllerRoute(
                name: "appointment",
                pattern: "Appointment/{action=Index}/{id?}",
                defaults: new { controller = "Appointment" });
        });
    }
}